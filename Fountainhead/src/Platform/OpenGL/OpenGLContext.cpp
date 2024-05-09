#include "fhpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)// ���캯������һ��ָ�� GLFWwindow ��ָ����Ϊ������������洢�ڳ�Ա���� m_WindowHandle �С����캯���л�����һ�����ԣ���鴫��� windowHandle �Ƿ�Ϊ null��ȷ��������������Ч�ԡ�
		: m_WindowHandle(windowHandle)
	{
		FH_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		FH_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);// ͨ�� glfwMakeContextCurrent���� m_WindowHandle ָ��Ĵ�������Ϊ��ǰ�̵߳Ļ�����ģ�����OpenGL�����ܹ���ȷִ�е�ǰ�ᡣ
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);// ʹ�� GLAD �������ز���ʼ��OpenGL����ָ�룬gladLoadGLLoader ͨ�� glfwGetProcAddress ָ�����ط�ʽ����һ���Ǳ���ģ���ΪOpenGL����ֻ��һ���淶�������ʵ���ɸ�Ӳ�������ṩ��GLAD�������ز�����Щʵ�֡�
		FH_CORE_ASSERT(status, "Failed to initialize Glad!");
		// �����ǰʹ�õ�OpenGL�����Ĺ�Ӧ�̡���Ⱦ���Ͱ汾��Ϣ������ڵ��Ժ�ȷ����������Էǳ��а�����
		FH_CORE_INFO("OpenGL Info");
		FH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()// ���� glfwSwapBuffers ������ǰ�󻺳�������˫����ģʽ�У����е���Ⱦ���������ں�̨����������ɵģ�����ʾ������ǰ̨���������С�������������������ζ�Ű���Ⱦ�õ�ͼ����ʾ����������ʼ����һ������������Ⱦ�µ�һ֡���������Լ��ٻ���˺�ѣ�����û����顣
	{
		FH_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);//����������
	}
}