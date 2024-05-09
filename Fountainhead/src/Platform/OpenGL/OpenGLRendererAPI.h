#pragma once

#include "Fountainhead/Renderer/RendererAPI.h"

namespace Fountainhead {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;// 负责设置OpenGL的初始状态，可能包括加载必要的扩展、设置默认的渲染状态等。
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;// 接收四个参数，用于定义渲染的视区（Viewport）。视区定义了渲染结果显示在窗口的哪个部分，以及这部分的大小。

		virtual void SetClearColor(const glm::vec4& color) override;// 接收一个 glm::vec4 类型的颜色值，用于设置渲染窗口清除时的背景颜色。
		virtual void Clear() override;// 清除屏幕和其他相关的缓冲区（如深度缓冲）。这通常在新的渲染帧开始前执行，以准备屏幕用于下一次绘制。

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;// 接收一个顶点数组的引用，用于执行索引绘制操作。这是一种高效的绘制方式，可以通过索引来重用顶点，常用于绘制复杂的三维模型。
	};


}