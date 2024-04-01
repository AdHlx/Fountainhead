#include "fhpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		FH_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);//创建当前上下文
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FH_CORE_ASSERT(status, "Failed to initialize Glad!");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);//交换缓冲区
	}
}