#pragma once

#include <glm/glm.hpp>

namespace Fountainhead {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);// 定义了正交投影的视图边界，初始化投影矩阵和视图矩阵。

		void SetProjection(float left, float right, float bottom, float top);// 重新设置投影矩阵的边界，并更新投影矩阵。
		// 获取和设置摄像机的位置。设置位置后，会重新计算视图矩阵。
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		// 获取和设置摄像机的旋转角度。设置旋转后，也会重新计算视图矩阵。
		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		// 分别返回投影矩阵、视图矩阵和它们的组合（视图投影矩阵）。视图投影矩阵通常用于顶点数据的最终变换，直接应用于顶点着色器中。
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();// 当摄像机的位置或旋转改变时，调用此方法重新计算视图矩阵。通过创建一个变换矩阵来实现的，该矩阵首先应用旋转（围绕Z轴，因为是2D视图），然后应用平移。
	private:
		glm::mat4 m_ProjectionMatrix;//投影矩阵
		glm::mat4 m_ViewMatrix;//视图矩阵，相机实际变换矩阵的逆矩阵
		glm::mat4 m_ViewProjectionMatrix;//暂存视图矩阵

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };//追踪位置
		float m_Rotation = 0.0f;//追踪旋转
	};

}