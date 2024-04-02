#include "fhpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Fountainhead {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//示例代码更改而来https://www.khronos.org/opengl/wiki/Shader_Compilation
		//创建一个空的顶点着色器句柄
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//向 GL 发送顶点着色器源代码
		//std::string 的 .c_str 是以 NULL 字符结束的
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		//编译顶点着色器
		glCompileShader(vertexShader);
		//检查编译是否成功
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			//获取日志消息长度，说明为什么没有编译成功
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength中包括NULL字符
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);//把所有的信息推入infoLog向量

			//我们不再需要着色器了
			glDeleteShader(vertexShader);

			FH_CORE_ERROR("{0}", infoLog.data());
			FH_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		//创建一个空的片段着色器句柄
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//向 GL 发送片段着色器源代码
		//std::string 的 .c_str 是以 NULL 字符结束的。
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		//编译片段着色器
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength 包括 NULL 字符
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			//我们不再需要着色器了
			glDeleteShader(fragmentShader);
			//任选其一,不要泄露着色器
			glDeleteShader(vertexShader);

			FH_CORE_ERROR("{0}", infoLog.data());
			FH_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		//顶点着色器和片段着色器编译成功
		//现在是将它们连接到程序中的时候了
		//获取程序对象
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;//将两个着色器结合

		//将着色器附加到程序中
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		//链接我们的程序
		glLinkProgram(program);

		//注意这里的不同函数：glGetProgram* 而不是 glGetShader*
		//检查链接状态
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength 包括 NULL 字符
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			//我们不再需要这个程序了
			glDeleteProgram(program);
			//同样不要泄露着色器
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			FH_CORE_ERROR("{0}", infoLog.data());
			FH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		//链接成功后，始终分离着色器
		//链接之后，我们不需要实际的单个文件
		//类似于我们编译cpp，如果我们有多个翻译单元，它们会生成obj文件
		//当我们链接到exe文件后，我们便不再需要obj文件
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