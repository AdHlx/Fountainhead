#include "fhpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fountainhead {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;//指定使用哪一个API

}