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
		Application();// 构造函数初始化应用程序实例。
		virtual ~Application();// 析构函数负责清理资源。

		void Run();// 开始应用程序的主运行循环，负责处理事件、更新状态和渲染。
		// 处理传入的事件。
		void OnEvent(Event& e);
		// 管理层栈，用于添加新的层或覆盖层。
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }// 返回窗口引用
		// 提供了一个静态的接口来获取当前应用程序实例的引用。它是单例模式的一部分，确保整个程序中只有一个 Application 类的实例，并提供一个全局访问点。
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;// 保存窗口类的一个实例
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;// 控制运行循环是否继续。
		bool m_Minimized = false;// 标记窗口是否被最小化。
		LayerStack m_LayerStack;// 层栈创建在栈内存是，继承App类的生命周期
		float m_LastFrameTime = 0.0f;// 渲染最后一帧所使用的时间
	private:
		static Application* s_Instance;// 静态指针，用于实现单例模式，确保全局只有一个 Application 实例。
	};

	// 在客户端中定义，构造 Application 类的实例，是应用程序启动流程的一部分。
	Application* CreateApplication();
}