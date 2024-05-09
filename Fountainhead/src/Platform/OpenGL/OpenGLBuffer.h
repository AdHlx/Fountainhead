#pragma once

#include "Fountainhead/Renderer/Buffer.h"

namespace Fountainhead {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);// ����һ�鶥�����ݺ����ݴ�С����������һ��OpenGL���㻺������VBO�����������ݱ��ϴ���GPU������ͼ����Ⱦ��
		virtual ~OpenGLVertexBuffer();// �������������ڶ����������ڽ���ʱ�ͷ�OpenGL��������Դ��

		virtual void Bind() const override;// ���˶��㻺�����󶨵���ǰ��OpenGL�������У�ʹ���Ϊ��ǰ��Ķ��㻺���������Ķ�����Ʋ�����ʹ����������ݡ�
		virtual void Unbind() const override;// ���ǰ���㻺������ȷ������������������ı���������������ݡ�

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }// ���ض��㻺�����Ĳ��֣�BufferLayout�����ⶨ���˶������ݵ���֯�ṹ����ÿ��������������ͺ�˳��
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }// ���ö��㻺�����Ĳ��֣��������û����嶥��������λ�á���ɫ�����ߵ���Ϣ�Ĵ洢��ʽ��
	private:
		uint32_t m_RendererID;// OpenGL�����Ψһ��ʶ�������������ض��Ķ��㻺������
		BufferLayout m_Layout;// �����������ݲ��ֵ� BufferLayout ����
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);// �����������ݺ���������������һ��OpenGL������������IBO���������������ڶ��嶥����������Щ���㰴���ض�˳�����ͼ�εĻ�Ԫ���������Ρ�
		virtual ~OpenGLIndexBuffer();// �������������ͷ�������������Դ��
		// �ֱ����ڰ󶨺ͽ���������������󶨺󣬻��Ƶ��ý�ʹ����Щ������ȷ����δӶ��㻺��������ȡ���㡣
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }// ��������������������ͼ�λ���������ʹ������������ʱ��Ҫ����Ϣ����ȷ��Ҫ��Ⱦ��ͼԪ��Ŀ��
	private:
		uint32_t m_RendererID;// �붥�㻺�������ƣ�����OpenGLΪ���������������Ψһ��ʶ����
		uint32_t m_Count;// �洢��������������ʾ�����������а�������������
	};

}