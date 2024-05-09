#pragma once

#include <memory>

// 使用预定义宏来检测和定义编译平台。目前只支持 Windows x64 平台。对于 x86、MacOS、iOS、Android 和 Linux 平台均不支持，并在编译时产生错误。
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define FH_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC 存在于所有平台上。
 * 所以我们必须检查所有平台（按此顺序）
 * 确保我们是在 MAC 上运行
 * 而不是其他苹果平台 */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define FH_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define FH_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
/* 我们还必须在 __linux__ 之前检查 __ANDROID__
* 因为安卓是基于 linux 内核的
* 它已经定义了__linux__ */
#elif defined(__ANDROID__)
#define FH_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define FH_PLATFORM_LINUX
#error "Linux is not supported!"
#else
/* 未知编译器或平台 */
#error "Unknown platform!"
#endif // 平台检测结束

#ifdef FH_DEBUG
	#define FH_ENABLE_ASSERTS
#endif // FH_DEBUG

// 在调试模式下启用断言，用于验证假设和捕捉编程错误。断言失败会打印错误消息并中断执行(__debugbreak()).
#ifdef FH_ENABLE_ASSERTS
	#define FH_ASSERT(x, ...) { if(!(x)) { FH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FH_CORE_ASSERT(x, ...) { if(!(x)) {FH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FH_ASSERT(x, ...)
	#define FH_CORE_ASSERT(x, ...)
#endif
// 用于设置位字段
#define BIT(x) (1 << x)
// 简化事件处理函数的绑定语法，使用 std::bind 和占位符绑定成员函数和对象。
#define FH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Fountainhead {
	// Scope 是 std::unique_ptr 的别名，用于自动管理单一所有权的动态分配对象。CreateScope 用于创建 Scope 实例，简化 std::unique_ptr 的构造过程。
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	// Ref 是 std::shared_ptr 的别名，用于自动管理共享所有权的动态分配对象。CreateRef 用于创建 Ref 实例，简化 std::shared_ptr 的构造过程。
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}