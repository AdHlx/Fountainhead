#include "fhpch.h"
#include "Fountainhead/Renderer/Shader.h"

#include "Fountainhead/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Fountainhead {
	// 根据渲染API创建着色器，若API为OpenGL，则使用 OpenGLShader 类的构造函数加载着色器。
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
		}

		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	// 这个重载允许直接通过顶点和片段着色器的源代码创建着色器，这对于运行时编译着色器非常有用，特别是在开发过程中测试新的着色效果。
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	// 将着色器添加到库中，并使用指定的名称作为键。
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		FH_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	// 重载版本，从着色器对象中获取名称，并调用另一个 Add 方法。
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	// 加载着色器文件，并自动添加到着色器库中。从文件路径创建着色器。
	Fountainhead::Ref<Fountainhead::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	// 从文件路径创建着色器，并指定一个自定义名称。
	Fountainhead::Ref<Fountainhead::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	// 根据名称获取已存储的着色器。如果名称不存在，则触发断言。
	Fountainhead::Ref<Fountainhead::Shader> ShaderLibrary::Get(const std::string& name)
	{
		FH_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	// 检查指定名称的着色器是否已存在于库中。
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}