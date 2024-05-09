#pragma once

#include <glm/glm.hpp>

#include "Fountainhead/Renderer/VertexArray.h"

namespace Fountainhead {

	class RendererAPI
	{
	public:
		enum class API// ����ָ��֧�ֵ�ͼ��API���ࡣ
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;// ���麯�������ڳ�ʼ����ȾAPI��
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;// ���麯���������ӿڵĳߴ��λ�á�
		virtual void SetClearColor(const glm::vec4& color) = 0;// ���麯�������������Ļʱʹ�õ���ɫ��
		virtual void Clear() = 0;// ���麯�������������ǰ���ӿڻ���ȾĿ�꣬ͨ����ÿ����Ⱦ��֮֡ǰ���á�

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;// ���麯����ִ���������Ƶ��ã����ǻ��ڶ���������е���Ⱦ��������������Ⱦ���ӵļ����塣

		inline static API GetAPI() { return s_API; }// ��̬��Ա���������ڻ�ȡ��ǰ���õ�ͼ��API���͡�
		static Scope<RendererAPI> Create();// ��̬��Ա���������ݵ�ǰ���õ�API���ʹ�����Ӧ��RendererAPI����ʵ��������������ʱ�������û�����ѡ��ͬ��ͼ��APIʵ�֡�

	private:
		static API s_API;// ��̬��Ա���������ڴ洢��ǰʹ�õ�ͼ��API�����͡�
	};

}