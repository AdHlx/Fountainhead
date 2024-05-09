#pragma once

#include "Fountainhead.h"

class Sandbox2D : public Fountainhead::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;// �����ͼ�㱻��ӵ�ͼ��ջʱ���á�
	virtual void OnDetach() override;// �����ͼ���ͼ��ջ���Ƴ�ʱ���á�
	// ÿһ֡����һ�Σ����ڸ���ͼ���״̬��
	void OnUpdate(Fountainhead::Timestep ts) override;// ts������ʾ����һ֡����ǰ֡��ʱ������ͨ������ȷ����Ϸ��ƽ�����У�ʱ�䲽��������
	virtual void OnImGuiRender() override;// ������Ⱦͼ���ImGui����Ԫ��
	void OnEvent(Fountainhead::Event& e) override;// ��������������¼���
private:
	Fountainhead::OrthographicCameraController m_CameraController;// ��������������������ڿ���2D��ͼ�е��������

	// Temp
	Fountainhead::Ref<Fountainhead::VertexArray> m_SquareVA;// һ�����������������ã����ڴ洢��Ⱦ2D��������Ķ������ݡ�
	Fountainhead::Ref<Fountainhead::Shader> m_FlatColorShader;// һ����ɫ����������ã�����Ϊ2D�����ṩ��ɫ��䡣

	Fountainhead::Ref<Fountainhead::Texture2D> m_CheckerboardTexture;// һ��2D�����������ã����ڸ�2D�����ṩ���̸���ʽ������

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };// һ����ά������������2D�������ɫ��������ɫ��RGBA��ʽ��ʾ����Χ��0��1��
};