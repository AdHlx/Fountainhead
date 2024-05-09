#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>

namespace Fountainhead {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;// 定义了一个以微秒为单位的浮点数持续时间类型，用于更精确的时间测量。

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};// 存储性能分析结果的结构体，包含代码段名称、开始时间、运行时间和线程ID。

	struct InstrumentationSession
	{
		std::string Name;
	};// 定义一个性能监控会话，只包含会话名称。

	class Instrumentor
	{
	private:// 包含互斥锁以支持多线程操作，当前会话指针，和输出文件流对象。
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	public:
		Instrumentor()
			: m_CurrentSession(nullptr)// 默认构造函数，初始化当前会话为 nullptr。
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")// 开始一个新的监控会话，线程安全地打开输出文件，并记录会话开始。
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) {
				// 如果已经有一个当前会话，则在开始新的会话前关闭该会话。
				// 原会话的后续剖析输出将在 // 新打开的会话中结束。
				// 新打开的会话中。 这总比格式错误的
				// 剖析输出。
				if (Log::GetCoreLogger()) { // 边缘情况： BeginSession() 可能在 Log::Init() 之前
					FH_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open()) {
				m_CurrentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else {
				if (Log::GetCoreLogger()) { // 边缘情况： BeginSession() 可能在 Log::Init() 之前
					FH_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession()// 结束当前会话，线程安全地调用内部结束会话函数。
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)// 将性能分析结果以 JSON 格式写入文件，保证线程安全。
		{
			std::stringstream json;

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) {
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}
		// 提供全局访问点（单例模式），确保全局只有一个性能监控器实例。
		static Instrumentor& Get() {
			static Instrumentor instance;
			return instance;
		}

	private:
		// 写入 JSON 文件的头部和尾部，以及内部的会话结束处理。
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		// 注意：在调用 InternalEndSession() 之前，您必须已经拥有 m_Mutex 上的锁。
		// 调用 InternalEndSession()
		void InternalEndSession() {
			if (m_CurrentSession) {
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

	};
	// 自动计时器，用于测量代码块的执行时间。它在构造时开始计时，在析构或显示停止时结束计时，并将结果写入 Instrumentor。
	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

// 定义条件编译的宏，用于控制性能监控的启用与否。
#define FH_PROFILE 1
#if FH_PROFILE
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define FH_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define FH_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define FH_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define FH_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define FH_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define FH_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define FH_FUNC_SIG __func__
#else
#define FH_FUNC_SIG "FH_FUNC_SIG unknown!"
#endif

#define FH_PROFILE_BEGIN_SESSION(name, filepath) ::Fountainhead::Instrumentor::Get().BeginSession(name, filepath)
#define FH_PROFILE_END_SESSION() ::Fountainhead::Instrumentor::Get().EndSession()
#define FH_PROFILE_SCOPE(name) ::Fountainhead::InstrumentationTimer timer##__LINE__(name);
#define FH_PROFILE_FUNCTION() FH_PROFILE_SCOPE(FH_FUNC_SIG)
#else
#define FH_PROFILE_BEGIN_SESSION(name, filepath)
#define FH_PROFILE_END_SESSION()
#define FH_PROFILE_SCOPE(name)
#define FH_PROFILE_FUNCTION()
#endif