#pragma once

#include "Fountainhead.h"

class ExampleLayer : public Fountainhead::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;// ��ͼ�㸽�ӵ�ͼ��ջʱִ�еĳ�ʼ��������
	virtual void OnDetach() override;// ��ͼ���ͼ��ջ�Ƴ�ʱִ�е����������

	void OnUpdate(Fountainhead::Timestep ts) override;// ͼ��ÿ֡����ʱ���ã�ts ��ʾʱ�䲽������һ֡����һ֡��ʱ������
	virtual void OnImGuiRender() override;// ����ͼ��� ImGui ��Ⱦ���á�
	void OnEvent(Fountainhead::Event& e) override;// �����¼�

private:
	Fountainhead::ShaderLibrary m_ShaderLibrary;// ��ɫ���⣬���ڹ���ʹ洢��ɫ����Դ��
	Fountainhead::Ref<Fountainhead::Shader> m_Shader;// ����һ����ɫ�������ڳ������Ⱦ����
	Fountainhead::Ref<Fountainhead::VertexArray> m_VertexArray;// ����һ���������飬���ڴ洢�͹��������ݡ�

	Fountainhead::Ref<Fountainhead::Shader> m_FlatColorShader;// ר�����ڻ��Ƶ�ɫͼ�ε���ɫ����
	Fountainhead::Ref<Fountainhead::VertexArray> m_SquareVA;// ���ڻ��������εĶ������顣

	Fountainhead::Ref<Fountainhead::Texture2D> m_Texture;// ��������m_Texture ͨ�����ڳ��������Ӧ�á�

	Fountainhead::OrthographicCameraController m_CameraController;// ���������������������2D��ͼ���������
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };// ���ڶ�����������ɫ����ά��������ɫ��ʽΪRGB��
};