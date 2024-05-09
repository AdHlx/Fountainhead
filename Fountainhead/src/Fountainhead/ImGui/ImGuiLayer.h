#pragma once

#include "Fountainhead/Core/Layer.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/KeyEvent.h"
#include "Fountainhead/Events/MouseEvent.h"


namespace Fountainhead {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();// 初始化 ImGui 层，设置必要的起始状态。
		~ImGuiLayer();// 负责清理所有 ImGui 相关的资源。

		virtual void OnAttach() override;// 当层附加到层栈时调用，用于进行一次性的设置，如 ImGui 的初始化。
		virtual void OnDetach() override;// 当层从层栈中移除时调用，用于进行清理工作，如释放 ImGui 使用的资源。
		void Begin();// 开始一个 ImGui 渲染帧，在实际渲染 ImGui 组件之前调用。
		void End();// 结束一个 ImGui 渲染帧，进行渲染提交，在所有 ImGui 组件渲染完成后调用。
	private:
		float m_Time = 0.0f;
	};

}