#pragma once

#include "Fountainhead/Renderer/OrthographicCamera.h"

#include "Fountainhead/Renderer/Texture.h"

namespace Fountainhead {

	class Renderer2D
	{
	public:
		// ���ڳ�ʼ���͹ر���Ⱦ��
		static void Init();
		static void Shutdown();
		// ���ڿ�ʼ�ͽ�����Ⱦ����
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// ���ڻ����ı��Σ�����ָ��λ�á���С����ɫ������
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

}