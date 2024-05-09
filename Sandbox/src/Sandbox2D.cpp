#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// ���û��� Layer �Ĺ��캯��������ͼ������� "Sandbox2D"��
// m_CameraController(1280.0f / 720.0f)����ʼ�������������������������ĳ��������Ϊ1280 / 720��
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	// ���ܷ��������꣬�������ܼ�⡣
	FH_PROFILE_FUNCTION();
	// ���������������ļ���
	m_CheckerboardTexture = Fountainhead::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	// ʹ�����ܷ����꣬���ڼ����Դж�ػ�ͼ���Ƴ�ʱ�����ܡ�
	FH_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Fountainhead::Timestep ts)
{
	FH_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		// ����������ɫ�������Ļ��Ϊ�µ���Ⱦ֡��׼����
		FH_PROFILE_SCOPE("Renderer Prep");
		Fountainhead::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fountainhead::RenderCommand::Clear();
	}

	{
		// ���ƾ��Σ�quad����������������Ϊλ�á��ߴ����ɫ������
		FH_PROFILE_SCOPE("Renderer Draw");
		Fountainhead::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Fountainhead::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fountainhead::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Fountainhead::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Fountainhead::Renderer2D::EndScene();
	}
}
// ʹ�� ImGui �ⴴ��һ�����ô��ڣ������û�������ʱ�����������ɫ��
void Sandbox2D::OnImGuiRender()
{
	FH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
// ���¼����ݸ��������������������������������ƶ��¼���
void Sandbox2D::OnEvent(Fountainhead::Event& e)
{
	m_CameraController.OnEvent(e);
}