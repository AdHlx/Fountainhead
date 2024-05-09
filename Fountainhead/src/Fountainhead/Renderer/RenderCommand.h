#pragma once

#include "Fountainhead/Renderer/RendererAPI.h"

//ʵ�ʵ�ԭʼ��Ⱦָ���Renderer.h���ýӿ�
namespace Fountainhead {

	class RenderCommand
	{
	public:
		inline static void Init()// ��ʼ����ȾAPI����ͨ���漰������Ⱦ״̬����ʼ����Ⱦ�����ȡ����ö�Ӧ�� RendererAPI ʵ���� Init ������
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)// �����ӿڵĴ�С��λ�ã��ӿڶ�������Ⱦ�����ʾ�����򡣽�����������ݸ� RendererAPI �� SetViewport ������
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)// ���������Ļʱʹ�õ���ɫ��ͨ����ÿ����Ⱦ��ʼǰ���á�������ɫֵ�� RendererAPI �� SetClearColor ������
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()// �����Ļ��������ʹ��֮ǰͨ�� SetClearColor ���õ���ɫ������ RendererAPI �� Clear ������
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)// ִ�������������������Ⱦһ��Ԥ�ȶ���Ķ����ͨ�÷��������ݶ�����������õ� RendererAPI �� DrawIndexed ������
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;// ��̬��Ա���������� RendererAPI ��ʵ���������� RenderCommand ͨ��ͬһ�� RendererAPI ʵ�����õײ���ȾAPI��ȷ����Ⱦָ���ͳһ�͸�Ч����
	};

}