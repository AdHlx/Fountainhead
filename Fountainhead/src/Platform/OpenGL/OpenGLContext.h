#pragma once

#include "Fountainhead/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Fountainhead {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);// ����һ��ָ�� GLFWwindow ��ָ�룬����GLFW�����ڹ����ڵĽṹ��������ھ������OpenGL�����ĵĴ����͹���
		virtual void Init() override;// ���������������OpenGL�����ģ������봰�ھ���������κα�Ҫ�ĳ�ʼ�����衣��ͨ����������OpenGL��չ����ʹ��GLAD�⣩�������ӿڴ�С����ʼ���κα�Ҫ��OpenGL״̬�ȡ�Init ��������Ӧ�ó�������ʱ���ã�ȷ������OpenGL��Դ��ʹ��ǰ��ȷ��ʼ����
		virtual void SwapBuffers() override;// ��˫������Ⱦ�����У��˷������𽻻�ǰ�󻺳�����ʹ��������Ⱦ��֡������ʾ����Ļ�ϡ�������ÿ����Ⱦѭ����ĩβ���ã����ڸ��´����е�ͼ����ʾ��
	private:
		GLFWwindow* m_WindowHandle;// �洢����Ĵ��ھ����������OpenGL������������Ĵ��ڡ������Ա��������ķ����б����������ض��Ĵ��ڣ�ִ���罻���������Ȳ�����
	};

}