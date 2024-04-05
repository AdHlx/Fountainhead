#include "fhpch.h"
#include "VertexArray.h"

#include "Fountainhead/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fountainhead {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}