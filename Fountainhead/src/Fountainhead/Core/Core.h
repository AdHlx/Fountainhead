#pragma once

#include <memory>

#ifdef FH_PLATFORM_WINDOWS
#if FH_DYNAMIC_LINK
	#ifdef FH_BUILD_DLL
		#define FOUNTAINHEAD_API __declspec(dllexport)
	#else
		#define FOUNTAINHEAD_API __declspec(dllimport)
	#endif // FH_BUILD_DLL
#else
	#define FOUNTAINHEAD_API
#endif
#else
	#error Fountainhead only supports Windows!
#endif // FH_PLATFORM_WINDOWS

#ifdef FH_DEBUG
	#define FH_ENABLE_ASSERTS
#endif // FH_DEBUG


#ifdef FH_ENABLE_ASSERTS
	#define FH_ASSERT(x, ...) { if(!(x)) { FH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FH_CORE_ASSERT(x, ...) { if(!(x)) {FH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FH_ASSERT(x, ...)
	#define FH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Fountainhead {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}