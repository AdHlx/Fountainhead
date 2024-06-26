#include "fhpch.h"
#include "Fountainhead/Renderer/GraphicsContext.h"

#include "Fountainhead/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Fountainhead {
	// 基于当前配置的渲染API，创建一个具体的图形上下文对象。
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}