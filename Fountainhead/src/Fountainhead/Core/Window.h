#pragma once

#include "fhpch.h"

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	struct WindowProps//Windows�ϵ�Ĭ�ϴ�������
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Fountainhead Engine",
			unsigned int width = 1200,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};// ����ָ�����ڵı��⡢��Ⱥ͸߶ȣ�Ĭ��Ϊ "Fountainhead Engine"��1200 ��� 720 �ߡ�

	// ���ڴ��ڵ�����ϵͳ����
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;//һ�����¼�Ϊ����������void�ĺ���
		//��WindowsWindow.cpp�������¼�ʱ�����ǻ���¼����ȵ��¼��ص�����

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// ��������
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;// ���õ������¼�����ʱ�Ļص����������ڽ��¼����ݸ�Ӧ�ó���㴦��
		// Ȼ�����ǿ��԰��¼����������еĲ㣬������Ͼ��Ǵ�����������¼��ķ�ʽ�����������¼�
		virtual void SetVSync(bool enabled) = 0;// ���ڿ������ѯ��ֱͬ����
		virtual bool IsVSync() const = 0;
		// ����һ��ָ��ײ�ƽ̨���ڵ�ָ�룬������еײ���������á�
		virtual void* GetNativeWindow() const = 0;
		// ��̬���������ڴ�������ʵ��������ͨ�� WindowProps �Զ��崰�����ԡ�
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}