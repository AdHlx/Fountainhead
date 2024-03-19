#pragma once

#ifdef FH_PLATFORM_WINDOWS

extern Fountainhead::Application* Fountainhead::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Fountainhead::CreateApplication();
	app->Run();
	delete app;
}
#endif // FH_PLATFORM_WINDOWS
