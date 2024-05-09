#include "fhpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Fountainhead {

	//<------------VertexBuffer------------->
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)// ����һ��OpenGL���������󣬲������������ϴ���GPU��ʹ�� glCreateBuffers ������������glBindBuffer �󶨻������� GL_ARRAY_BUFFER Ŀ�꣬Ȼ�� glBufferData ���ڳ�ʼ�������������ݴ洢��
	{
		FH_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);// �����ݴ���gpu��GL_STATIC_DRAW ��ʾ���ݲ������ٻ�ı䣬�Ǹ���OpenGL����Ż��洢��һ�ַ�ʽ��
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()// ������Դ������ glDeleteBuffers ɾ�������Ļ���������ֹ��Դй¶��
	{
		FH_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const// ͨ�� glBindBuffer ����ǰ�������󶨵� GL_ARRAY_BUFFER��
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const// �� GL_ARRAY_BUFFER �İ�����Ϊ0�����ǽ��ǰ�������ı�׼������
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//<------------IndexBuffer------------->

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)// �����ڶ��㻺�����Ĺ��캯�������󶨵���Ŀ���� GL_ELEMENT_ARRAY_BUFFER������ר�����������Ļ�������
		: m_Count(count)
	{
		FH_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);// �����ݴ���gpu��indices ��һ�������������ݵ����飬count ������������glBufferData ����Щ���ݳ�ʼ�����������������ݴ洢��
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()// �붥�㻺�������ƣ�����ɾ���������������ͷ�OpenGL��Դ��
	{
		FH_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const// �������������󶨵� GL_ELEMENT_ARRAY_BUFFER��
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const// ������������������� GL_ELEMENT_ARRAY_BUFFER �İ�Ϊ0��
	{
		FH_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}