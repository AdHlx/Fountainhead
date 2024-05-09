#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// 调用基类 Layer 的构造函数，传递图层的名称 "Sandbox2D"。
// m_CameraController(1280.0f / 720.0f)：初始化正交摄像机控制器，摄像机的长宽比设置为1280 / 720。
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	// 性能分析函数宏，用于性能监测。
	FH_PROFILE_FUNCTION();
	// 创建并加载纹理文件。
	m_CheckerboardTexture = Fountainhead::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	// 使用性能分析宏，用于监测资源卸载或图层移除时的性能。
	FH_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Fountainhead::Timestep ts)
{
	FH_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		// 设置清屏颜色并清空屏幕，为新的渲染帧做准备。
		FH_PROFILE_SCOPE("Renderer Prep");
		Fountainhead::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fountainhead::RenderCommand::Clear();
	}

	{
		// 绘制矩形（quad），函数参数依次为位置、尺寸和颜色或纹理。
		FH_PROFILE_SCOPE("Renderer Draw");
		Fountainhead::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Fountainhead::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fountainhead::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Fountainhead::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Fountainhead::Renderer2D::EndScene();
	}
}
// 使用 ImGui 库创建一个设置窗口，允许用户在运行时调整方块的颜色。
void Sandbox2D::OnImGuiRender()
{
	FH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
// 将事件传递给摄像机控制器，处理如键盘输入和鼠标移动事件。
void Sandbox2D::OnEvent(Fountainhead::Event& e)
{
	m_CameraController.OnEvent(e);
}