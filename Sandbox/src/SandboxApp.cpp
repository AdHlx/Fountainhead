#include <Fountainhead.h>

class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}