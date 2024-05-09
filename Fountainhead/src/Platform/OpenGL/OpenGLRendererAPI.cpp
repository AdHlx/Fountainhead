#include "fhpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Fountainhead {

	void OpenGLRendererAPI::Init()// 设置OpenGL的一些基本渲染状态，以保证渲染过程的正确性和视觉效果。
	{
		FH_PROFILE_FUNCTION();

		glEnable(GL_BLEND);// 启用混合并设置混合函数，这对于渲染半透明材料是必要的。使用 GL_SRC_ALPHA 和 GL_ONE_MINUS_SRC_ALPHA 作为混合参数，适用于基于透明度的典型混合。
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);// 启用深度测试以正确处理图形的前后关系。这确保了三维渲染中较近的物体能够遮挡较远的物体。
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)// 设置OpenGL渲染的视区，即决定了在窗口中渲染输出的具体区域。
	{
		glViewport(x, y, width, height);// 调用 glViewport 函数，传入视口的位置和大小。
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)// 设置清屏时使用的颜色
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()// 清除颜色和深度缓冲区，为新的渲染帧做准备。
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)//  执行基于索引的绘制，这是一种高效的绘制方式，可减少顶点重复定义带来的性能开销。
	{
		// 使用 glDrawElements，它是OpenGL中用于基于索引的绘制的函数。此函数需要指定绘制模式（这里是 GL_TRIANGLES 表示每三个索引定义一个三角形），索引数量，索引的数据类型（这里是 GL_UNSIGNED_INT），以及索引数据的位置（这里使用 nullptr，因为索引缓冲区已绑定）。
		// vertexArray->GetIndexBuffer()->GetCount() 调用获取索引数量，这表明了需要渲染多少个顶点来构建指定的几何形状。
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);// 在绘制后，解绑任何可能绑定的纹理，以避免意外修改纹理状态。
	}

}