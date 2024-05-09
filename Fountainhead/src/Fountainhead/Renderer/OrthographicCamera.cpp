#include "fhpch.h"
#include "Fountainhead/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Fountainhead {
	// glm::ortho��һ����������ͶӰ�����GLM�⺯��������������ͼ�ı߽�ͽ�Զ�ü�ƽ�档��ʼ����ͼ���� (m_ViewMatrix) Ϊ��λ���󣬳�ʼʱ�����û��λ�ƺ���ת��
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		FH_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	// ��������ͶӰ���󲢸�����ͼͶӰ����
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		FH_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	// ���¼�����ͼ����
	void OrthographicCamera::RecalculateViewMatrix()
	{
		FH_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));//ƽ�ƾ��󣬳�����ת����

		m_ViewMatrix = glm::inverse(transform);//��ת��������
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		/*
		ʹ�� glm::translate ����һ��ƽ�ƾ��󣬽�������ƶ��� m_Position ָ����λ�á�
		ʹ�� glm::rotate ����һ����ת���󣬽��������ת m_Rotation ָ���ĽǶȣ���Z�ᣬ������2D��ͼ����
		��󣬼����������任�ĸ��ϱ任����Ȼ��ȡ�棨��Ϊ������Ҫ����������任����������꣬����ͼ���꣩��
		*/
	}

}