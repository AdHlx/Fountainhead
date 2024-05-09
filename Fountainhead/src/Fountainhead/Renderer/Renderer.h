#pragma once

#include "Fountainhead/Renderer/RenderCommand.h"

#include "Fountainhead/Renderer/OrthographicCamera.h"
#include "Fountainhead/Renderer/Shader.h"

namespace Fountainhead {

	class Renderer
	{
	public:
		// 用于初始化和关闭渲染器
		static void Init();
		static void Shutdown();
		// 在窗口大小改变时调用，用于更新渲染器相关的数据
		static void OnWindowResize(uint32_t width, uint32_t height);
		// 用于开始和结束渲染场景
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		// 用于提交渲染任务，包括着色器、顶点数组和变换矩阵
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		// 获取渲染器使用的API
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;// 用于存储视图投影矩阵
		};

		static SceneData* s_SceneData;
	};

}