#pragma once

#include "Fountainhead/Layer.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/KeyEvent.h"
#include "Fountainhead/Events/MouseEvent.h"


namespace Fountainhead {

	class FOUNTAINHEAD_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		//virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
	//	void OnEvent(Event& event) override;
	//private:
	//	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	//	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	//	bool OnMouseMovedEvent(MouseMovedEvent& e);
	//	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	//	bool OnKeyPressedEvent(KeyPressedEvent& e);
	//	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	//	bool OnKeyTypedEvent(KeyTypedEvent& e);
	//	bool OnWindowResizeEvent(WindowResizeEvent& e);
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}