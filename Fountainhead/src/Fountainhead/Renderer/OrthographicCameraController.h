#pragma once

#include "Fountainhead/Renderer/OrthographicCamera.h"
#include "Fountainhead/Core/Timestep.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/MouseEvent.h"

namespace Fountainhead {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);// ���տ�߱ȣ�aspectRatio�����Ƿ�������ת�ı�־��rotation������ʼ����Ӧ�ĳ�Ա������������������ĳ�ʼͶӰ��

		void OnUpdate(Timestep ts);// �����������λ�ú���ת��
		void OnEvent(Event& e);// �����ⲿ�¼�������Ӧ�ص����������
		// �ṩ���ڲ� OrthographicCamera ��������ã������ⲿֱ�ӷ��ʺ��޸������״̬��
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		// ��ȡ���������ż������ż���ı�ʱ��������������ͶӰ����
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);// �����������¼����������ż���
		bool OnWindowResized(WindowResizeEvent& e);// �����ڴ�С�仯�¼�������������Ŀ�߱Ⱥ�ͶӰ����
	private:
		float m_AspectRatio;// ������ͼ�Ŀ�߱Ⱥ����ż���
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;// ָʾ�Ƿ�������ת��
		// �������λ�ú���ת�Ƕȡ����������ƽ�ƺ���ת���ٶȡ�
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}