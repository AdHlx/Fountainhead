#pragma once

#include "Fountainhead/Core/Core.h"

#ifdef FH_PLATFORM_WINDOWS

extern Fountainhead::Application* Fountainhead::CreateApplication();

int main(int argc, char** argv)
{
	Fountainhead::Log::Init();// ��ʼ����־ϵͳ��

	// ��¼Ӧ�ó��������׶ε��������ݣ����� CreateApplication �ĵ��á�
	FH_PROFILE_BEGIN_SESSION("Startup", "FountainheadProfile-Startup.json");
	// ����Ӧ�ó���ʵ��������ͨ���ڿͻ��˶���� CreateApplication ����ʵ�֣�������Ӧ�ó���ľ�����Ϊ�ͳ�ʼ��״̬��
	auto app = Fountainhead::CreateApplication();
	FH_PROFILE_END_SESSION();
	// ��¼Ӧ�ó���������ʱ���������ݣ���Ҫ�� app->Run() ���������ܡ�
	FH_PROFILE_BEGIN_SESSION("Runtime", "FountainheadProfile-Runtime.json");
	app->Run();// ����Ӧ�ó��򣬽�����ѭ���������¼������º���Ⱦ��
	FH_PROFILE_END_SESSION();
	// ��¼Ӧ�ó���رս׶ε��������ݣ���Ҫ��Ӧ�ó����������١�
	FH_PROFILE_BEGIN_SESSION("Startup", "FountainheadProfile-Shutdown.json");
	delete app;// ����Ӧ�ó���ʵ�����ͷ���Դ��
	FH_PROFILE_END_SESSION();
}
#endif // FH_PLATFORM_WINDOWS
