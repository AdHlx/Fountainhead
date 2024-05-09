#pragma once

#include "Fountainhead/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Fountainhead {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);// ���ļ�·��������ɫ��Դ���룬����Ԥ����ͱ��롣���ֹ��캯��������ֱ�Ӵ��ļ��ж�ȡ��ɫ�����롣
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);// ����ֱ��ͨ���ṩ�����Ƭ����ɫ����Դ������������ɫ�������ַ����ṩ�˸��������ԣ�������Դ���������ڴ��е������
		virtual ~OpenGLShader();// �������������������е�OpenGL��Դ��ȷ����Դ����ȷ�ͷš�
		// �����������ֱ����ڼ���ͽ�����ǰ����ɫ��������OpenGL�У���ɫ��������Ҫ����������������Ⱦ������
		virtual void Bind() const override;
		virtual void Unbind() const override;
		// �ṩһϵ�� Set ����������������ɫ���е�uniform��������Щ������װ�˶� glUniform �ĵ��ã������ⲿ����ɫ��״̬�Ĺ���
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }
		// ��Щ�����Ǿ���ʵ������ɫ������ͳһ�����Ĺ��ܡ������ϴ��������͵����ݣ����������������������;���
		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);// ��ȡ�ļ����ݵ��ַ�����ͨ�����ڼ�����ɫ�����롣
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);// ����ɫ���������Ԥ�������ܰ��������ض���ǻ�ָ�����Ӧ��ͬ����ɫ���׶Σ����㡢Ƭ�Σ���
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);// ���� GLenum ���ͣ�������ɫ�������ࣨ�綥����ɫ����Ƭ����ɫ������ֵ�ǰ�����ɫ��Դ������ַ���������ӳ�����ṩ��ÿ�����͵���ɫ���������󣬲����������ӳ�һ����������ɫ�����򣬽�ԭʼ����ɫ��Դ����ת����GPU��ִ�еĹ�������ɫ������
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}