#include "fhpch.h"
#include "Fountainhead/Renderer/Renderer.h"
#include "Fountainhead/Renderer/Renderer2D.h"

namespace Fountainhead {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	// ��ʼ�����������ڳ�ʼ����Ⱦ����
	void Renderer::Init()
	{
		FH_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}
	// �رպ��������ڹر���Ⱦ����
	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}
	// �ڴ��ڴ�С�仯ʱ���ã������ӿڴ�С��
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	// ��ʼ��Ⱦ������������ͼͶӰ����Ϊ�������ͼͶӰ����
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}
	// �ύ��Ⱦ�����ø�������ɫ������������ͱ任���������Ⱦ��
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();// ����ɫ����������ɫ���е���ͼͶӰ����ͱ任����
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();// �󶨶������飬��ʹ����Ⱦ������л��ơ�
		RenderCommand::DrawIndexed(vertexArray);
	}


}