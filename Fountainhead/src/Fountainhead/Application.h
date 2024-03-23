#pragma once

#include "Core.h"
#include "Window.h"
#include "Fountainhead/Events/ApplicationEvent.h"

namespace Fountainhead {
	class FOUNTAINHEAD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;//保存窗口类的一个实例
		bool m_Running = true;
	};

	//To defined in CLIENT
	Application* CreateApplication();
}

