#pragma once

#include "Fountainhead/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Fountainhead {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);// 接收一个指向 GLFWwindow 的指针，这是GLFW库用于管理窗口的结构。这个窗口句柄用于OpenGL上下文的创建和管理。
		virtual void Init() override;// 这个方法负责设置OpenGL上下文，包括与窗口句柄关联的任何必要的初始化步骤。这通常包括加载OpenGL扩展（如使用GLAD库）、设置视口大小、初始化任何必要的OpenGL状态等。Init 方法是在应用程序启动时调用，确保所有OpenGL资源在使用前正确初始化。
		virtual void SwapBuffers() override;// 在双缓冲渲染配置中，此方法负责交换前后缓冲区，使得最新渲染的帧可以显示到屏幕上。这是在每个渲染循环的末尾调用，用于更新窗口中的图像显示。
	private:
		GLFWwindow* m_WindowHandle;// 存储传入的窗口句柄，这是与OpenGL上下文相关联的窗口。这个成员变量在类的方法中被用来引用特定的窗口，执行如交换缓冲区等操作。
	};

}