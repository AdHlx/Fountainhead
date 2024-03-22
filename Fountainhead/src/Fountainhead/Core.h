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

#define BIT(x) (1 << x)