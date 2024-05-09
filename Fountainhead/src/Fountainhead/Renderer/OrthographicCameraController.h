#pragma once

#include "Fountainhead/Renderer/OrthographicCamera.h"
#include "Fountainhead/Core/Timestep.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/MouseEvent.h"

namespace Fountainhead {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);// 接收宽高比（aspectRatio）和是否启用旋转的标志（rotation），初始化相应的成员变量，并配置摄像机的初始投影。

		void OnUpdate(Timestep ts);// 更新摄像机的位置和旋转。
		void OnEvent(Event& e);// 处理外部事件，并相应地调整摄像机。
		// 提供对内部 OrthographicCamera 对象的引用，允许外部直接访问和修改摄像机状态。
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		// 获取和设置缩放级别，缩放级别改变时，会更新摄像机的投影矩阵。
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);// 处理鼠标滚轮事件来调整缩放级别。
		bool OnWindowResized(WindowResizeEvent& e);// 处理窗口大小变化事件，更新摄像机的宽高比和投影矩阵。
	private:
		float m_AspectRatio;// 控制视图的宽高比和缩放级别。
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;// 指示是否允许旋转。
		// 摄像机的位置和旋转角度。控制摄像机平移和旋转的速度。
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}