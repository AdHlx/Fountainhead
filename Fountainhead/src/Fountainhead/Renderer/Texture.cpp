#include "fhpch.h"
#include "Fountainhead/Renderer/Texture.h"

#include "Fountainhead/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Fountainhead {
	// 创建一个指定宽高的二维纹理。这通常用于需要空白纹理或自定义内容纹理的场景（例如渲染到纹理，或动态纹理更新）。
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
		}

		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	// 从指定的文件路径加载一个二维纹理。
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}