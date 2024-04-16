#pragma once

#include "Fountainhead.h"

class ExampleLayer : public Fountainhead::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Fountainhead::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Fountainhead::Event& e) override;

private:
	Fountainhead::ShaderLibrary m_ShaderLibrary;
	Fountainhead::Ref<Fountainhead::Shader> m_Shader;
	Fountainhead::Ref<Fountainhead::VertexArray> m_VertexArray;

	Fountainhead::Ref<Fountainhead::Shader> m_FlatColorShader;
	Fountainhead::Ref<Fountainhead::VertexArray> m_SquareVA;

	Fountainhead::Ref<Fountainhead::Texture2D> m_Texture, m_ChernoLogoTexture;

	Fountainhead::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};