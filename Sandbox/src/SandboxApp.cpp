#include <Fountainhead.h>

class Sandbox : public Fountainhead::Application //Sandbox类继承了Fountainhead::Application
{
	public:
		Sandbox()
		{

		}
		~Sandbox()
		{

		}
};

//实现CreateApplication
Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}