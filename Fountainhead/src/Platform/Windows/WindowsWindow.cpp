#include "fhpch.h"
#include "WindowsWindow.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/MouseEvent.h"
#include "Fountainhead/Events/KeyEvent.h"

namespace Fountainhead {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)//�����������Ҫ���ľ��Ǽ�����־
	{
		FH_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	//��������ʱ�����ù��캯�������캯������Init()����������������������
	Window* Window::Create(const WindowProps& props)//Create������ʵ��
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)//��ʼ��glfw���������ǵĴ���
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FH_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			FH_CORE_ASSERT(success, "Could not intialize GLFW!");//ʹ�ö��Լ���Ƿ��������
			glfwSetErrorCallback(GLFWErrorCallback);//��Ӵ���ص�����
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);//����glfw����
		glfwMakeContextCurrent(m_Window);//������ǰ������
		glfwSetWindowUserPointer(m_Window, &m_Data);//����һ�������û�ָ�룬�����¼��ص�
		//������������ڽṹ�����void*���洫����û�����ָ�룬��������ǿ���������ʹ������������Ӵ����л���û�����ָ��
		SetVSync(true);//��ֱͬ������

		//����GLFW�ص�
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)//��Ҫ����һ�����ڣ���һ�����ڴ�С�ı�֮��Ҫ���õĺ���
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);//�ⷵ��һ��void*��������Ҫת�ͳ���ȷ������
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);//��������Ҫ����Fountainhead�¼�
			data.EventCallback(event);//��ɴ������ڴ�С�¼����ҵ���
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)//���ڹر��¼�
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)//�����¼�
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)//��������glfw���еģ������Ҫת��ΪFountainhead�İ�����
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)//��갴���¼�
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)//�������¼�
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)//����ƶ��¼�
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()//���ٴ���
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();//��ȡ�¼�
		glfwSwapBuffers(m_Window);//����������
	}

	void WindowsWindow::SetVSync(bool enabled)//��ֱͬ�����ú���
	{
		if (enabled)
			glfwSwapInterval(1);//�����������n��n����n��ͬ�����൱��1/n��ʾ��֡��
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;//�������Ƿ����ã���Ϊ�����޷���glfw�в�ѯ�������
	}

	bool WindowsWindow::IsVSync() const//�����Ƿ���˴�ֱͬ��
	{
		return m_Data.VSync;
	}
}