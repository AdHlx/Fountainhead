#include "fhpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Fountainhead {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());//我们使用unique_ptr所以在应用程序终止时，我们不必自己删除窗口
		//Window::Create()会调用构造函数，然后会调用Init()
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//用std::bind绑定一个成员函数，用宏简化
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)//一个适配器，本质上就是把层或者覆层推入层栈
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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));//如果是关闭操作，就调度到OnWindowClosed这个函数

		FH_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)//反向遍历
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