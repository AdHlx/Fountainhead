#pragma once

#include <glm/glm.hpp>

namespace Fountainhead {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);// ����������ͶӰ����ͼ�߽磬��ʼ��ͶӰ�������ͼ����

		void SetProjection(float left, float right, float bottom, float top);// ��������ͶӰ����ı߽磬������ͶӰ����
		// ��ȡ�������������λ�á�����λ�ú󣬻����¼�����ͼ����
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		// ��ȡ���������������ת�Ƕȡ�������ת��Ҳ�����¼�����ͼ����
		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		// �ֱ𷵻�ͶӰ������ͼ��������ǵ���ϣ���ͼͶӰ���󣩡���ͼͶӰ����ͨ�����ڶ������ݵ����ձ任��ֱ��Ӧ���ڶ�����ɫ���С�
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();// ���������λ�û���ת�ı�ʱ�����ô˷������¼�����ͼ����ͨ������һ���任������ʵ�ֵģ��þ�������Ӧ����ת��Χ��Z�ᣬ��Ϊ��2D��ͼ����Ȼ��Ӧ��ƽ�ơ�
	private:
		glm::mat4 m_ProjectionMatrix;//ͶӰ����
		glm::mat4 m_ViewMatrix;//��ͼ�������ʵ�ʱ任����������
		glm::mat4 m_ViewProjectionMatrix;//�ݴ���ͼ����

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };//׷��λ��
		float m_Rotation = 0.0f;//׷����ת
	};

}