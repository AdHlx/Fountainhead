#pragma once

#include "Fountainhead/Core/Core.h"

#include "Fountainhead/Core/Window.h"
#include "Fountainhead/Core/LayerStack.h"
#include "Fountainhead/Events/ApplicationEvent.h"

#include "Fountainhead/Core/Timestep.h"

#include "Fountainhead/ImGui/ImGuiLayer.h"

namespace Fountainhead {
	class Application
	{
	public:
		Application();// ���캯����ʼ��Ӧ�ó���ʵ����
		virtual ~Application();// ������������������Դ��

		void Run();// ��ʼӦ�ó����������ѭ�����������¼�������״̬����Ⱦ��
		// ��������¼���
		void OnEvent(Event& e);
		// �����ջ����������µĲ�򸲸ǲ㡣
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }// ���ش�������
		// �ṩ��һ����̬�Ľӿ�����ȡ��ǰӦ�ó���ʵ�������á����ǵ���ģʽ��һ���֣�ȷ������������ֻ��һ�� Application ���ʵ�������ṩһ��ȫ�ַ��ʵ㡣
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;// ���洰�����һ��ʵ��
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;// ��������ѭ���Ƿ������
		bool m_Minimized = false;// ��Ǵ����Ƿ���С����
		LayerStack m_LayerStack;// ��ջ������ջ�ڴ��ǣ��̳�App�����������
		float m_LastFrameTime = 0.0f;// ��Ⱦ���һ֡��ʹ�õ�ʱ��
	private:
		static Application* s_Instance;// ��ָ̬�룬����ʵ�ֵ���ģʽ��ȷ��ȫ��ֻ��һ�� Application ʵ����
	};

	// �ڿͻ����ж��壬���� Application ���ʵ������Ӧ�ó����������̵�һ���֡�
	Application* CreateApplication();
}