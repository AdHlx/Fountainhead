#pragma once

#include <glm/glm.hpp>

#include "Fountainhead/Renderer/VertexArray.h"

namespace Fountainhead {

	class RendererAPI
	{
	public:
		enum class API// 用于指定支持的图形API种类。
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;// 纯虚函数，用于初始化渲染API。
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;// 纯虚函数，设置视口的尺寸和位置。
		virtual void SetClearColor(const glm::vec4& color) = 0;// 纯虚函数，设置清除屏幕时使用的颜色。
		virtual void Clear() = 0;// 纯虚函数，用于清除当前的视口或渲染目标，通常在每次渲染新帧之前调用。

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;// 纯虚函数，执行索引绘制调用，这是基于顶点数组进行的渲染操作，常用于渲染复杂的几何体。

		inline static API GetAPI() { return s_API; }// 静态成员函数，用于获取当前设置的图形API类型。
		static Scope<RendererAPI> Create();// 静态成员函数，根据当前设置的API类型创建相应的RendererAPI对象实例。这允许运行时根据配置或需求选择不同的图形API实现。

	private:
		static API s_API;// 静态成员变量，用于存储当前使用的图形API的类型。
	};

}