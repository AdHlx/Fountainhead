#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Fountainhead {
	class FOUNTAINHEAD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To defined in CLIENT
	Application* CreateApplication();
}

