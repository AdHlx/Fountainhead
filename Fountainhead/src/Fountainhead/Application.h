#pragma once

#include "Core.h"

namespace Fountainhead {
	class FOUNTAINHEAD_API Application
	{
	public:
		Application();
		virtual ~Application();	//将解析方法变为虚方法，因为这个类会被继承

		void Run();
	};

	//在客户端中定义
	Application* CreateApplication();
}

