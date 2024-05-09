#pragma once

#include <memory>

// ʹ��Ԥ����������Ͷ������ƽ̨��Ŀǰֻ֧�� Windows x64 ƽ̨������ x86��MacOS��iOS��Android �� Linux ƽ̨����֧�֣����ڱ���ʱ��������
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
/* TARGET_OS_MAC ����������ƽ̨�ϡ�
 * �������Ǳ���������ƽ̨������˳��
 * ȷ���������� MAC ������
 * ����������ƻ��ƽ̨ */
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
/* ���ǻ������� __linux__ ֮ǰ��� __ANDROID__
* ��Ϊ��׿�ǻ��� linux �ں˵�
* ���Ѿ�������__linux__ */
#elif defined(__ANDROID__)
#define FH_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define FH_PLATFORM_LINUX
#error "Linux is not supported!"
#else
/* δ֪��������ƽ̨ */
#error "Unknown platform!"
#endif // ƽ̨������

#ifdef FH_DEBUG
	#define FH_ENABLE_ASSERTS
#endif // FH_DEBUG

// �ڵ���ģʽ�����ö��ԣ�������֤����Ͳ�׽��̴��󡣶���ʧ�ܻ��ӡ������Ϣ���ж�ִ��(__debugbreak()).
#ifdef FH_ENABLE_ASSERTS
	#define FH_ASSERT(x, ...) { if(!(x)) { FH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FH_CORE_ASSERT(x, ...) { if(!(x)) {FH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FH_ASSERT(x, ...)
	#define FH_CORE_ASSERT(x, ...)
#endif
// ��������λ�ֶ�
#define BIT(x) (1 << x)
// ���¼��������İ��﷨��ʹ�� std::bind ��ռλ���󶨳�Ա�����Ͷ���
#define FH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Fountainhead {
	// Scope �� std::unique_ptr �ı����������Զ�����һ����Ȩ�Ķ�̬�������CreateScope ���ڴ��� Scope ʵ������ std::unique_ptr �Ĺ�����̡�
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	// Ref �� std::shared_ptr �ı����������Զ�����������Ȩ�Ķ�̬�������CreateRef ���ڴ��� Ref ʵ������ std::shared_ptr �Ĺ�����̡�
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}