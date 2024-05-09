#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Fountainhead {

	class Shader// ������࣬������������ɫ���������ʵ�ֵĽӿڡ�
	{
	public:
		virtual ~Shader() = default;
		// ������������ɫ������ʵ�ֵĽӿڣ������󶨺ͽ����ɫ����������ɫ��������Uniforms�����Լ���ȡ��ɫ��������
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;// ������ɫ�������ơ�
		// �ṩ���ַ�ʽ������ɫ����ֱ�Ӵ��ļ�·������ʹ�ö����Ƭ����ɫ����Դ���ַ�����������������ɫ��������ԣ��ر����ڿ����п��ٲ����µ���ɫЧ����
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary// ����һ����ɫ���ļ��ϣ�����洢�������͹�����ɫ������
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader); //�����ɫ�������У�����ָ�����ơ�
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);// ������ɫ�����ļ�·�������ָ�����ƣ����Ը����Ʊ��档
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		// �������ƻ�ȡ�Ѽ��ص���ɫ����
		Ref<Shader> Get(const std::string& name);
		// ���ָ�����Ƶ���ɫ���Ƿ��Ѵ����ڿ��С�
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;// �洢��ɫ�����ã����ַ�������Ϊ����
	};

}