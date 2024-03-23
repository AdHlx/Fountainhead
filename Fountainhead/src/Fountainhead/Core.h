#pragma once

#ifdef FH_PLATFORM_WINDOWS
	#ifdef FH_BUILD_DLL
		#define FOUNTAINHEAD_API __declspec(dllexport)
	#else
		#define FOUNTAINHEAD_API __declspec(dllimport)
	#endif // FH_BUILD_DLL
#else
	#error Fountainhead only supports Windows!
#endif // FH_PLATFORM_WINDOWS

#ifdef FH_ENABLE_ASSERTS
	#define FH_ASSERT(x, ...) { if(!(x)) { FH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FH_CORE_ASSERT(x, ...) { if(!(x)) {FH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FH_ASSERT(x, ...)
	#define FH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)