#include "fhpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fountainhead {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}