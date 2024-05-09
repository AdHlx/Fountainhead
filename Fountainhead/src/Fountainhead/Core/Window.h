#pragma once

#include "fhpch.h"

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	struct WindowProps//Windows上的默认窗口属性
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
	};// 允许指定窗口的标题、宽度和高度，默认为 "Fountainhead Engine"、1200 宽和 720 高。

	// 基于窗口的桌面系统界面
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;//一个以事件为参数，返回void的函数
		//在WindowsWindow.cpp中生成事件时，我们会把事件调度到事件回调函数

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// 窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;// 设置当窗口事件发生时的回调函数，用于将事件传递给应用程序层处理。
		// 然后我们可以把事件传播到所有的层，这基本上就是处理各种类型事件的方式，包括窗口事件
		virtual void SetVSync(bool enabled) = 0;// 用于开启或查询垂直同步。
		virtual bool IsVSync() const = 0;
		// 返回一个指向底层平台窗口的指针，允许进行底层操作或配置。
		virtual void* GetNativeWindow() const = 0;
		// 静态方法，用于创建窗口实例，允许通过 WindowProps 自定义窗口属性。
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}