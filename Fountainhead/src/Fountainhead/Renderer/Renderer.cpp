#include "fhpch.h"
#include "Fountainhead/Renderer/Renderer.h"
#include "Fountainhead/Renderer/Renderer2D.h"

namespace Fountainhead {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	// 初始化函数，用于初始化渲染器。
	void Renderer::Init()
	{
		FH_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}
	// 关闭函数，用于关闭渲染器。
	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}
	// 在窗口大小变化时调用，设置视口大小。
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	// 开始渲染场景，设置视图投影矩阵为相机的视图投影矩阵。
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}
	// 提交渲染任务，用给定的着色器、顶点数组和变换矩阵进行渲染。
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();// 绑定着色器，设置着色器中的视图投影矩阵和变换矩阵。
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();// 绑定顶点数组，并使用渲染命令进行绘制。
		RenderCommand::DrawIndexed(vertexArray);
	}


}