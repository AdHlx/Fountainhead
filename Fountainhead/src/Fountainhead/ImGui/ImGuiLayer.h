#pragma once

#include "Fountainhead/Core/Layer.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/KeyEvent.h"
#include "Fountainhead/Events/MouseEvent.h"


namespace Fountainhead {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();// ��ʼ�� ImGui �㣬���ñ�Ҫ����ʼ״̬��
		~ImGuiLayer();// ������������ ImGui ��ص���Դ��

		virtual void OnAttach() override;// ���㸽�ӵ���ջʱ���ã����ڽ���һ���Ե����ã��� ImGui �ĳ�ʼ����
		virtual void OnDetach() override;// ����Ӳ�ջ���Ƴ�ʱ���ã����ڽ��������������ͷ� ImGui ʹ�õ���Դ��
		void Begin();// ��ʼһ�� ImGui ��Ⱦ֡����ʵ����Ⱦ ImGui ���֮ǰ���á�
		void End();// ����һ�� ImGui ��Ⱦ֡��������Ⱦ�ύ�������� ImGui �����Ⱦ��ɺ���á�
	private:
		float m_Time = 0.0f;
	};

}