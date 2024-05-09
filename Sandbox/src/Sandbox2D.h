#pragma once

#include "Fountainhead.h"

class Sandbox2D : public Fountainhead::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;// 当这个图层被添加到图层栈时调用。
	virtual void OnDetach() override;// 当这个图层从图层栈中移除时调用。
	// 每一帧调用一次，用于更新图层的状态。
	void OnUpdate(Fountainhead::Timestep ts) override;// ts参数表示从上一帧到当前帧的时间间隔，通常用于确保游戏的平滑运行（时间步方法）。
	virtual void OnImGuiRender() override;// 用于渲染图层的ImGui界面元素
	void OnEvent(Fountainhead::Event& e) override;// 处理输入和其他事件。
private:
	Fountainhead::OrthographicCameraController m_CameraController;// 正交摄像机控制器，用于控制2D视图中的摄像机。

	// Temp
	Fountainhead::Ref<Fountainhead::VertexArray> m_SquareVA;// 一个顶点数组对象的引用，用于存储渲染2D方块所需的顶点数据。
	Fountainhead::Ref<Fountainhead::Shader> m_FlatColorShader;// 一个着色器对象的引用，用于为2D方块提供单色填充。

	Fountainhead::Ref<Fountainhead::Texture2D> m_CheckerboardTexture;// 一个2D纹理对象的引用，用于给2D方块提供棋盘格样式的纹理。

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };// 一个四维向量，定义了2D方块的颜色。这里颜色用RGBA格式表示，范围从0到1。
};