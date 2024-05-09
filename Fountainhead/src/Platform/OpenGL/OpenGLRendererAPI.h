#pragma once

#include "Fountainhead/Renderer/RendererAPI.h"

namespace Fountainhead {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;// ��������OpenGL�ĳ�ʼ״̬�����ܰ������ر�Ҫ����չ������Ĭ�ϵ���Ⱦ״̬�ȡ�
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;// �����ĸ����������ڶ�����Ⱦ��������Viewport����������������Ⱦ�����ʾ�ڴ��ڵ��ĸ����֣��Լ��ⲿ�ֵĴ�С��

		virtual void SetClearColor(const glm::vec4& color) override;// ����һ�� glm::vec4 ���͵���ɫֵ������������Ⱦ�������ʱ�ı�����ɫ��
		virtual void Clear() override;// �����Ļ��������صĻ�����������Ȼ��壩����ͨ�����µ���Ⱦ֡��ʼǰִ�У���׼����Ļ������һ�λ��ơ�

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;// ����һ��������������ã�����ִ���������Ʋ���������һ�ָ�Ч�Ļ��Ʒ�ʽ������ͨ�����������ö��㣬�����ڻ��Ƹ��ӵ���άģ�͡�
	};


}