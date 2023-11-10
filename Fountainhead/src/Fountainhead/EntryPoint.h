#pragma once

#ifdef FH_PLATFORM_WINDOWS

extern Fountainhead::Application* Fountainhead::CreateApplication();	//返回Fountainhead::Application指针

int main(int argc, char** argv)
{
	Fountainhead::Log::Init();
	FH_CORE_WARN("Initialized Log!");
	int a = 5;
	FH_INFO("Hello! Var={0}", a);
	auto app = Fountainhead::CreateApplication();
	app->Run();
	delete app;
}	//创建应用程序
#endif // Windows系统入口
