#pragma once

#include "RenderCommand.h"

namespace Fountainhead {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }//获取渲染器使用的API
	};

}