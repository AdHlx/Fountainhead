#pragma once

#include "Fountainhead/Renderer/OrthographicCamera.h"

#include "Fountainhead/Renderer/Texture.h"

namespace Fountainhead {

	class Renderer2D
	{
	public:
		// 用于初始化和关闭渲染器
		static void Init();
		static void Shutdown();
		// 用于开始和结束渲染场景
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// 用于绘制四边形，可以指定位置、大小、颜色或纹理
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

}