#include <Fountainhead.h>
#include <Fountainhead/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
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