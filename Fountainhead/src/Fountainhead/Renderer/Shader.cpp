#include "fhpch.h"
#include "Fountainhead/Renderer/Shader.h"

#include "Fountainhead/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Fountainhead {
	// ������ȾAPI������ɫ������APIΪOpenGL����ʹ�� OpenGLShader ��Ĺ��캯��������ɫ����
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
	// �����������ֱ��ͨ�������Ƭ����ɫ����Դ���봴����ɫ�������������ʱ������ɫ���ǳ����ã��ر����ڿ��������в����µ���ɫЧ����
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
	// ����ɫ����ӵ����У���ʹ��ָ����������Ϊ����
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		FH_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	// ���ذ汾������ɫ�������л�ȡ���ƣ���������һ�� Add ������
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	// ������ɫ���ļ������Զ���ӵ���ɫ�����С����ļ�·��������ɫ����
	Fountainhead::Ref<Fountainhead::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	// ���ļ�·��������ɫ������ָ��һ���Զ������ơ�
	Fountainhead::Ref<Fountainhead::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	// �������ƻ�ȡ�Ѵ洢����ɫ����������Ʋ����ڣ��򴥷����ԡ�
	Fountainhead::Ref<Fountainhead::Shader> ShaderLibrary::Get(const std::string& name)
	{
		FH_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	// ���ָ�����Ƶ���ɫ���Ƿ��Ѵ����ڿ��С�
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}