#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Fountainhead {

	class Shader// 抽象基类，定义了所有着色器对象必须实现的接口。
	{
	public:
		virtual ~Shader() = default;
		// 定义了所有着色器必须实现的接口，包括绑定和解绑着色器，设置着色器参数（Uniforms），以及获取着色器的名称
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;// 返回着色器的名称。
		// 提供两种方式加载着色器：直接从文件路径或者使用顶点和片段着色器的源码字符串。这允许灵活的着色器编译策略，特别是在开发中快速测试新的着色效果。
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary// 管理一个着色器的集合，允许存储、检索和管理着色器对象。
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader); //添加着色器到库中，可以指定名称。
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);// 加载着色器从文件路径，如果指定名称，则以该名称保存。
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		// 根据名称获取已加载的着色器。
		Ref<Shader> Get(const std::string& name);
		// 检查指定名称的着色器是否已存在于库中。
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;// 存储着色器引用，以字符串名称为键。
	};

}