#include "fhpch.h"
#include "Fountainhead/Core/Application.h"

#include "Fountainhead/Core/Log.h"

#include "Fountainhead/Renderer/Renderer.h"

#include "Fountainhead/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Fountainhead {

	Application* Application::s_Instance = nullptr;
	//初始化应用程序实例，确保只有一个应用实例 (s_Instance), 并设置窗口事件回调。初始化渲染器和 ImGui 层。
	Application::Application()
	{
		FH_PROFILE_FUNCTION();

		FH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();//我们使用unique_ptr所以在应用程序终止时，我们不必自己删除窗口
		//Window::Create()会调用构造函数，然后会调用Init()
		m_Window->SetEventCallback(FH_BIND_EVENT_FN(Application::OnEvent));
		//用std::bind绑定一个成员函数，用宏简化

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	// 清理渲染器资源，保证应用退出时资源得到正确释放。
	Application::~Application()
	{
		FH_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)//一个适配器，本质上就是把层或者覆层推入层栈
	{
		FH_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		FH_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	// 分发事件到相应的处理函数，如果是窗口关闭或调整大小事件，特别处理以更新应用状态。遍历层堆栈，传递事件到每一个层，直到事件被处理。
	void Application::OnEvent(Event& e)
	{
		FH_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FH_BIND_EVENT_FN(Application::OnWindowClose));//如果是关闭操作，就调度到OnWindowClosed这个函数
		dispatcher.Dispatch<WindowResizeEvent>(FH_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)//反向遍历
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	// 维持应用的主循环，包括更新层的状态、处理 GUI 渲染，并更新窗口状态。使用 Timestep 计算帧间隔，支持时间依赖的更新逻辑。
	void Application::Run()
	{
		FH_PROFILE_FUNCTION();

		while (m_Running)//层更新与imgui更新
		{
			FH_PROFILE_FUNCTION();

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					FH_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					FH_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		FH_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}