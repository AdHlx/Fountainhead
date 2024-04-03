#pragma once

#include "Core.h"

#include "Window.h"
#include "Fountainhead/LayerStack.h"
#include "Fountainhead/Events/ApplicationEvent.h"

#include "Fountainhead/ImGui/ImGuiLayer.h"

#include "Fountainhead/Renderer/Shader.h"
#include "Fountainhead/Renderer/Buffer.h"

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

		inline Window& GetWindow() { return *m_Window; }//返回窗口引用

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;//保存窗口类的一个实例
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;//层栈创建在栈内存是，继承App类的生命周期

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	//To defined in CLIENT
	Application* CreateApplication();
}