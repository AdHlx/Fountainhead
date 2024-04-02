#include "fhpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Fountainhead {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//ʾ��������Ķ���https://www.khronos.org/opengl/wiki/Shader_Compilation
		//����һ���յĶ�����ɫ�����
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//�� GL ���Ͷ�����ɫ��Դ����
		//std::string �� .c_str ���� NULL �ַ�������
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		//���붥����ɫ��
		glCompileShader(vertexShader);
		//�������Ƿ�ɹ�
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			//��ȡ��־��Ϣ���ȣ�˵��Ϊʲôû�б���ɹ�
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength�а���NULL�ַ�
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);//�����е���Ϣ����infoLog����

			//���ǲ�����Ҫ��ɫ����
			glDeleteShader(vertexShader);

			FH_CORE_ERROR("{0}", infoLog.data());
			FH_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		//����һ���յ�Ƭ����ɫ�����
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//�� GL ����Ƭ����ɫ��Դ����
		//std::string �� .c_str ���� NULL �ַ������ġ�
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		//����Ƭ����ɫ��
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength ���� NULL �ַ�
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			//���ǲ�����Ҫ��ɫ����
			glDeleteShader(fragmentShader);
			//��ѡ��һ,��Ҫй¶��ɫ��
			glDeleteShader(vertexShader);

			FH_CORE_ERROR("{0}", infoLog.data());
			FH_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		//������ɫ����Ƭ����ɫ������ɹ�
		//�����ǽ��������ӵ������е�ʱ����
		//��ȡ�������
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;//��������ɫ�����

		//����ɫ�����ӵ�������
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		//�������ǵĳ���
		glLinkProgram(program);

		//ע������Ĳ�ͬ������glGetProgram* ������ glGetShader*
		//�������״̬
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength ���� NULL �ַ�
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			//���ǲ�����Ҫ���������
			glDeleteProgram(program);
			//ͬ����Ҫй¶��ɫ��
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			FH_CORE_ERROR("{0}", infoLog.data());
			FH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		//���ӳɹ���ʼ�շ�����ɫ��
		//����֮�����ǲ���Ҫʵ�ʵĵ����ļ�
		//���������Ǳ���cpp����������ж�����뵥Ԫ�����ǻ�����obj�ļ�
		//���������ӵ�exe�ļ������Ǳ㲻����Ҫobj�ļ�
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}
	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}
	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

}