#pragma once

#include "Fountainhead/Core/Core.h"

#ifdef FH_PLATFORM_WINDOWS

extern Fountainhead::Application* Fountainhead::CreateApplication();

int main(int argc, char** argv)
{
	Fountainhead::Log::Init();// 初始化日志系统。

	// 记录应用程序启动阶段的性能数据，包括 CreateApplication 的调用。
	FH_PROFILE_BEGIN_SESSION("Startup", "FountainheadProfile-Startup.json");
	// 创建应用程序实例，这是通过在客户端定义的 CreateApplication 函数实现，允许定制应用程序的具体行为和初始化状态。
	auto app = Fountainhead::CreateApplication();
	FH_PROFILE_END_SESSION();
	// 记录应用程序主运行时的性能数据，主要是 app->Run() 方法的性能。
	FH_PROFILE_BEGIN_SESSION("Runtime", "FountainheadProfile-Runtime.json");
	app->Run();// 运行应用程序，进入主循环，处理事件、更新和渲染。
	FH_PROFILE_END_SESSION();
	// 记录应用程序关闭阶段的性能数据，主要是应用程序对象的销毁。
	FH_PROFILE_BEGIN_SESSION("Startup", "FountainheadProfile-Shutdown.json");
	delete app;// 清理应用程序实例，释放资源。
	FH_PROFILE_END_SESSION();
}
#endif // FH_PLATFORM_WINDOWS
