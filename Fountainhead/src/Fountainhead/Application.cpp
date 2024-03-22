#include "fhpch.h"
#include "Application.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Log.h"

namespace Fountainhead {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			FH_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			FH_TRACE(e);
		}

		while (true);
	}
}