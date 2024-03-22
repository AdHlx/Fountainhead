#include "fhpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Fountainhead {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");//%T��ʱ�䣬%n����־��������Ķ���ʵ�ʵ���Ϣ
		s_CoreLogger = spdlog::stdout_color_mt("Fountainhead");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}