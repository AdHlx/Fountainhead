#include <Fountainhead.h>

class ExampleLayer : public Fountainhead::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		FH_INFO("ExampleLayer::Update");
	}

	void OnEvent(Fountainhead::Event& event) override
	{
		FH_TRACE("{0}", event);
	}

};

class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Fountainhead::ImGuiLayer());//推入ImGuiLayer作为覆层
	}

	~Sandbox()
	{

	}
};

Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}