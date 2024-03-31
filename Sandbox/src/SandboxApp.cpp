#include <Fountainhead.h>

#include "imgui/imgui.h"
class ExampleLayer : public Fountainhead::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Fountainhead::Input::IsKeyPressed(FH_KEY_TAB))
			FH_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Fountainhead::Event& event) override
	{
		if (event.GetEventType() == Fountainhead::EventType::KeyPressed)
		{
			Fountainhead::KeyPressedEvent& e = (Fountainhead::KeyPressedEvent&)event;
			if (Fountainhead::Input::IsKeyPressed(FH_KEY_TAB))
				FH_TRACE("Tab key is pressed (event)!");
			FH_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Fountainhead::ImGuiLayer());//推入ImGuiLayer作为覆层
	}

	~Sandbox()
	{

	}
};

Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}