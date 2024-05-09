#include "fhpch.h"
#include "Fountainhead/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Fountainhead {
	// glm::ortho是一个生成正交投影矩阵的GLM库函数，它定义了视图的边界和近远裁剪平面。初始化视图矩阵 (m_ViewMatrix) 为单位矩阵，初始时摄像机没有位移和旋转。
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		FH_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	// 重新设置投影矩阵并更新视图投影矩阵。
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		FH_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	// 重新计算视图矩阵
	void OrthographicCamera::RecalculateViewMatrix()
	{
		FH_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));//平移矩阵，乘以旋转矩阵

		m_ViewMatrix = glm::inverse(transform);//反转矩阵求逆
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		/*
		使用 glm::translate 创建一个平移矩阵，将摄像机移动到 m_Position 指定的位置。
		使用 glm::rotate 创建一个旋转矩阵，将摄像机旋转 m_Rotation 指定的角度（绕Z轴，适用于2D视图）。
		最后，计算这两个变换的复合变换矩阵，然后取逆（因为我们需要从世界坐标变换到摄像机坐标，即视图坐标）。
		*/
	}

}