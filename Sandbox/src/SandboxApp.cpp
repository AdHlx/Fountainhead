#include <Fountainhead.h>

class Sandbox : public Fountainhead::Application //Sandbox��̳���Fountainhead::Application
{
	public:
		Sandbox()
		{

		}
		~Sandbox()
		{

		}
};

//ʵ��CreateApplication
Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}