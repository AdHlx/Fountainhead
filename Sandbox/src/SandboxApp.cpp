#include <Fountainhead.h>

//#include "imgui/imgui.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, - Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public Fountainhead::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		auto cam = camera(5.0f, { 0.5f, 0.5f });
	}

	void OnUpdate() override
	{
		if (Fountainhead::Input::IsKeyPressed(FH_KEY_TAB))
			FH_TRACE("Tab key is pressed (poll)!");
	}

	//virtual void OnImGuiRender() override
	//{
	//	ImGui::Begin("Test");
	//	ImGui::Text("Hello World");
	//	ImGui::End();
	//}

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