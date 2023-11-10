#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Fountainhead {
	class FOUNTAINHEAD_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger>	s_CoreLogger;
		static std::shared_ptr<spdlog::logger>	s_ClientLogger;
	};
}

//Core log macros
#define FH_CORE_TRACE(...)		::Fountainhead::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FH_CORE_INFO(...)		::Fountainhead::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FH_CORE_WARN(...)		::Fountainhead::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FH_CORE_ERROR(...)		::Fountainhead::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FH_CORE_FATAL(...)		::Fountainhead::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define FH_TRACE(...)		::Fountainhead::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FH_INFO(...)		::Fountainhead::Log::GetClientLogger()->info(__VA_ARGS__)
#define FH_WARN(...)		::Fountainhead::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FH_ERROR(...)		::Fountainhead::Log::GetClientLogger()->error(__VA_ARGS__)
#define FH_FATAL(...)		::Fountainhead::Log::GetClientLogger()->fatal(__VA_ARGS__)