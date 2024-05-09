#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Timestep.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");// 初始化层并可选地命名该层，如果不指定名称，默认为 "Layer"。
		virtual ~Layer();// 虚析构函数，确保派生类能正确清理。

		virtual void OnAttach() {}// 当层被推入层栈时调用，用于执行初始化任务。
		virtual void OnDetach() {}// 当层从层栈中移除时调用，用于执行清理任务。
		virtual void OnUpdate(Timestep ts) {}// 每帧调用一次以更新层的状态，Timestep 参数提供了自上一帧以来的时间差，支持帧率无关的动画和逻辑更新。
		virtual void OnImGuiRender() {}// 用于执行 ImGui 渲染调用，常用于调试界面的构建。
		virtual void OnEvent(Event& event) {}// 处理传入的事件。

		inline const std::string& GetName() const { return m_DebugName; }// 返回层的名称，用于调试或日志记录。
	protected:
		std::string m_DebugName;// 存储着层的名称，用于调试的目的
	};

}