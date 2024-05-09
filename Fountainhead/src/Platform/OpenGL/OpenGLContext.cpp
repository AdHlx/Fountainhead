#include "fhpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)// 构造函数接收一个指向 GLFWwindow 的指针作为参数，并将其存储在成员变量 m_WindowHandle 中。构造函数中还包括一个断言，检查传入的 windowHandle 是否为 null，确保后续操作的有效性。
		: m_WindowHandle(windowHandle)
	{
		FH_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		FH_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);// 通过 glfwMakeContextCurrent，将 m_WindowHandle 指向的窗口设置为当前线程的活动上下文，这是OpenGL命令能够正确执行的前提。
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);// 使用 GLAD 库来加载并初始化OpenGL函数指针，gladLoadGLLoader 通过 glfwGetProcAddress 指定加载方式。这一步是必须的，因为OpenGL本身只是一个规范，具体的实现由各硬件厂商提供，GLAD帮助加载并绑定这些实现。
		FH_CORE_ASSERT(status, "Failed to initialize Glad!");
		// 输出当前使用的OpenGL驱动的供应商、渲染器和版本信息，这对于调试和确保软件兼容性非常有帮助。
		FH_CORE_INFO("OpenGL Info");
		FH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()// 调用 glfwSwapBuffers 来交换前后缓冲区，在双缓冲模式中，所有的渲染操作都是在后台缓冲区上完成的，而显示则是在前台缓冲区进行。交换这两个缓冲区意味着把渲染好的图像显示出来，并开始在另一个缓冲区上渲染新的一帧。这样可以减少画面撕裂，提高用户体验。
	{
		FH_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);//交换缓冲区
	}
}