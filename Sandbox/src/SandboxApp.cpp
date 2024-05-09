#include <Fountainhead.h>
#include <Fountainhead/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"
// 定义了一个名为Sandbox的类，它继承自Fountainhead命名空间下的Application类
class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());// 推入Sandbox2D图层到应用程序的图层栈中
		//PushLayer(new ExampleLayer());// 推入ExampleLayer图层到应用程序的图层栈中
	}

	~Sandbox()
	{

	}
};
// 个全局函数，用于创建并返回一个Fountainhead应用程序的指针
Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}