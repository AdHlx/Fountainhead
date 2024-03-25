#include "fhpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Fountainhead {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());//����ʹ��unique_ptr������Ӧ�ó�����ֹʱ�����ǲ����Լ�ɾ������
		//Window::Create()����ù��캯����Ȼ������Init()
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//��std::bind��һ����Ա�������ú��
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)//һ���������������Ͼ��ǰѲ���߸��������ջ
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));//����ǹرղ������͵��ȵ�OnWindowClosed�������

		FH_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)//�������
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}