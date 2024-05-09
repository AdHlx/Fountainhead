#pragma once

#include <memory>
#include "Buffer.h"

namespace Fountainhead {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;// �󶨶���������󵽵�ǰ����Ⱦ�����ġ������ڽ��л�ͼ����ǰ׼�������������ݵı�׼���衣
		virtual void Unbind() const = 0;// ��󶥵���������Ա���������������Ա��󶨺�ʹ�á��������ڹ�����Ⱦ������״̬��������Ⱦ����

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;// ��һ�����㻺������ӵ����������С���������������������㻺������ÿ�����㻺�������԰�����ͬ����Ķ������ݡ�
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;// �����������������������������ڶ��嶥���������������Ч�����ö������ݣ��Ż��ڴ�ʹ�ú���Ⱦ���ܡ�

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;// �����붥��������������ж��㻺�����������б��������ⲿ���ʺͼ������ӵĶ��㻺������
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;// ���ص�ǰ���õ����������������á����ṩ��һ�ּ����������鵱ǰʹ�õ������������ķ�ʽ��

		static Ref<VertexArray> Create();// ����һ����������ʵ��������һ������������������ʵ�ʵ���ȾAPI�����ʵ����͵� VertexArray �������磬��ʹ��OpenGLʱ�����ᴴ��һ���ض���OpenGL�� VertexArray ʵ�֡�
	};

}