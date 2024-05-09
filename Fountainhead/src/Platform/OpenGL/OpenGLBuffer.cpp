#include "fhpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Fountainhead {

	//<------------VertexBuffer------------->
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)// 创建一个OpenGL缓冲区对象，并将顶点数据上传到GPU。使用 glCreateBuffers 创建缓冲区，glBindBuffer 绑定缓冲区到 GL_ARRAY_BUFFER 目标，然后 glBufferData 用于初始化缓冲区的数据存储。
	{
		FH_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);// 将数据传入gpu，GL_STATIC_DRAW 表示数据不会或很少会改变，是告诉OpenGL如何优化存储的一种方式。
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()// 清理资源，调用 glDeleteBuffers 删除创建的缓冲区，防止资源泄露。
	{
		FH_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const// 通过 glBindBuffer 将当前缓冲区绑定到 GL_ARRAY_BUFFER。
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const// 将 GL_ARRAY_BUFFER 的绑定重置为0，这是解绑当前缓冲区的标准方法。
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//<------------IndexBuffer------------->

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)// 类似于顶点缓冲区的构造函数，但绑定到的目标是 GL_ELEMENT_ARRAY_BUFFER，这是专门用于索引的缓冲区。
		: m_Count(count)
	{
		FH_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);// 将数据传入gpu，indices 是一个包含索引数据的数组，count 是索引数量，glBufferData 用这些数据初始化索引缓冲区的数据存储。
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()// 与顶点缓冲区类似，负责删除索引缓冲区，释放OpenGL资源。
	{
		FH_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const// 将索引缓冲区绑定到 GL_ELEMENT_ARRAY_BUFFER。
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const// 解绑索引缓冲区，设置 GL_ELEMENT_ARRAY_BUFFER 的绑定为0。
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}