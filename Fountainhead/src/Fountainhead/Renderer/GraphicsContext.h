#pragma once

namespace Fountainhead {
	// 抽象化图形上下文的接口，实现具体的渲染实现（如OpenGL、DirectX等）与应用程序逻辑分离。
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;// 初始化图形上下文，设置必要的状态以及准备好渲染流程。
		virtual void SwapBuffers() = 0;// 交换前后缓冲区

		static Scope<GraphicsContext> Create(void* window);// 根据传入的窗口句柄（或指针）创建一个具体的图形上下文对象。
	};

}