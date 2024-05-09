#pragma once

#include "Fountainhead.h"

class ExampleLayer : public Fountainhead::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;// 当图层附加到图层栈时执行的初始化操作。
	virtual void OnDetach() override;// 当图层从图层栈移除时执行的清理操作。

	void OnUpdate(Fountainhead::Timestep ts) override;// 图层每帧更新时调用，ts 表示时间步，即上一帧到这一帧的时间间隔。
	virtual void OnImGuiRender() override;// 用于图层的 ImGui 渲染调用。
	void OnEvent(Fountainhead::Event& e) override;// 处理事件

private:
	Fountainhead::ShaderLibrary m_ShaderLibrary;// 着色器库，用于管理和存储着色器资源。
	Fountainhead::Ref<Fountainhead::Shader> m_Shader;// 引用一个着色器，用于常规的渲染任务。
	Fountainhead::Ref<Fountainhead::VertexArray> m_VertexArray;// 引用一个顶点数组，用于存储和管理顶点数据。

	Fountainhead::Ref<Fountainhead::Shader> m_FlatColorShader;// 专门用于绘制单色图形的着色器。
	Fountainhead::Ref<Fountainhead::VertexArray> m_SquareVA;// 用于绘制正方形的顶点数组。

	Fountainhead::Ref<Fountainhead::Texture2D> m_Texture;// 引用纹理，m_Texture 通常用于常规的纹理应用。

	Fountainhead::OrthographicCameraController m_CameraController;// 正交摄像机控制器，控制2D视图的摄像机。
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };// 用于定义正方形颜色的三维向量，颜色格式为RGB。
};