#pragma once

namespace Fountainhead {
	// ����ͼ�������ĵĽӿڣ�ʵ�־������Ⱦʵ�֣���OpenGL��DirectX�ȣ���Ӧ�ó����߼����롣
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;// ��ʼ��ͼ�������ģ����ñ�Ҫ��״̬�Լ�׼������Ⱦ���̡�
		virtual void SwapBuffers() = 0;// ����ǰ�󻺳���

		static Scope<GraphicsContext> Create(void* window);// ���ݴ���Ĵ��ھ������ָ�룩����һ�������ͼ�������Ķ���
	};

}