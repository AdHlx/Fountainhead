#pragma once

#include "Core.h"

#include "Window.h"
#include "Fountainhead/LayerStack.h"
#include "Fountainhead/Events/ApplicationEvent.h"

namespace Fountainhead {
	class FOUNTAINHEAD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;//���洰�����һ��ʵ��
		bool m_Running = true;
		LayerStack m_LayerStack;//��ջ������ջ�ڴ��ǣ��̳�App�����������
	};

	//To defined in CLIENT
	Application* CreateApplication();
}