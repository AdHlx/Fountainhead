#include <Fountainhead.h>
#include <Fountainhead/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"
// ������һ����ΪSandbox���࣬���̳���Fountainhead�����ռ��µ�Application��
class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());// ����Sandbox2Dͼ�㵽Ӧ�ó����ͼ��ջ��
		//PushLayer(new ExampleLayer());// ����ExampleLayerͼ�㵽Ӧ�ó����ͼ��ջ��
	}

	~Sandbox()
	{

	}
};
// ��ȫ�ֺ��������ڴ���������һ��FountainheadӦ�ó����ָ��
Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}