#pragma once

#include "Fountainhead/Renderer/RenderCommand.h"

#include "Fountainhead/Renderer/OrthographicCamera.h"
#include "Fountainhead/Renderer/Shader.h"

namespace Fountainhead {

	class Renderer
	{
	public:
		// ���ڳ�ʼ���͹ر���Ⱦ��
		static void Init();
		static void Shutdown();
		// �ڴ��ڴ�С�ı�ʱ���ã����ڸ�����Ⱦ����ص�����
		static void OnWindowResize(uint32_t width, uint32_t height);
		// ���ڿ�ʼ�ͽ�����Ⱦ����
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		// �����ύ��Ⱦ���񣬰�����ɫ������������ͱ任����
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		// ��ȡ��Ⱦ��ʹ�õ�API
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;// ���ڴ洢��ͼͶӰ����
		};

		static SceneData* s_SceneData;
	};

}