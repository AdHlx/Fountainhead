#pragma once

#include "Fountainhead/Renderer/RendererAPI.h"

//实际的原始渲染指令，在Renderer.h调用接口
namespace Fountainhead {

	class RenderCommand
	{
	public:
		inline static void Init()// 初始化渲染API，这通常涉及设置渲染状态、初始化渲染环境等。调用对应的 RendererAPI 实例的 Init 方法。
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)// 设置视口的大小和位置，视口定义了渲染输出显示的区域。将具体参数传递给 RendererAPI 的 SetViewport 方法。
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)// 设置清除屏幕时使用的颜色，通常在每次渲染开始前调用。传递颜色值给 RendererAPI 的 SetClearColor 方法。
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()// 清除屏幕缓冲区，使用之前通过 SetClearColor 设置的颜色。调用 RendererAPI 的 Clear 方法。
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)// 执行索引绘制命令，这是渲染一组预先定义的顶点的通用方法。传递顶点数组的引用到 RendererAPI 的 DrawIndexed 方法。
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;// 静态成员变量，持有 RendererAPI 的实例。这允许 RenderCommand 通过同一个 RendererAPI 实例调用底层渲染API，确保渲染指令的统一和高效管理。
	};

}