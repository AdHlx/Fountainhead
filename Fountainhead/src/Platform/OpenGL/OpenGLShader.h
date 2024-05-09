#pragma once

#include "Fountainhead/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Fountainhead {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);// 从文件路径加载着色器源代码，进行预处理和编译。这种构造函数适用于直接从文件中读取着色器代码。
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);// 允许直接通过提供顶点和片段着色器的源代码来创建着色器。这种方法提供了更大的灵活性，适用于源代码已在内存中的情况。
		virtual ~OpenGLShader();// 析构函数负责清理所有的OpenGL资源，确保资源被正确释放。
		// 这两个方法分别用于激活和解除激活当前的着色器程序。在OpenGL中，着色器程序需要被激活后才能用于渲染操作。
		virtual void Bind() const override;
		virtual void Unbind() const override;
		// 提供一系列 Set 方法，用于设置着色器中的uniform变量。这些方法封装了对 glUniform 的调用，简化了外部对着色器状态的管理。
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }
		// 这些方法是具体实现向着色器发送统一变量的功能。包括上传各种类型的数据，如整数、浮点数、向量和矩阵。
		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);// 读取文件内容到字符串，通常用于加载着色器代码。
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);// 对着色器代码进行预处理，可能包括解析特定标记或指令，以适应不同的着色器阶段（顶点、片段）。
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);// 键是 GLenum 类型，代表着色器的种类（如顶点着色器或片段着色器），值是包含着色器源代码的字符串。编译映射中提供的每种类型的着色器，检查错误，并将它们链接成一个完整的着色器程序，将原始的着色器源代码转换成GPU能执行的功能性着色器程序。
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}