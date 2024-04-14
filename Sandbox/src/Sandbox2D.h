#pragma once

#include "Fountainhead.h"

class Sandbox2D : public Fountainhead::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Fountainhead::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Fountainhead::Event& e) override;
private:
	Fountainhead::OrthographicCameraController m_CameraController;

	// Temp
	Fountainhead::Ref<Fountainhead::VertexArray> m_SquareVA;
	Fountainhead::Ref<Fountainhead::Shader> m_FlatColorShader;

	Fountainhead::Ref<Fountainhead::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};