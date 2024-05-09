#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Timestep.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");// ��ʼ���㲢��ѡ�������ò㣬�����ָ�����ƣ�Ĭ��Ϊ "Layer"��
		virtual ~Layer();// ������������ȷ������������ȷ����

		virtual void OnAttach() {}// ���㱻�����ջʱ���ã�����ִ�г�ʼ������
		virtual void OnDetach() {}// ����Ӳ�ջ���Ƴ�ʱ���ã�����ִ����������
		virtual void OnUpdate(Timestep ts) {}// ÿ֡����һ���Ը��²��״̬��Timestep �����ṩ������һ֡������ʱ��֧��֡���޹صĶ������߼����¡�
		virtual void OnImGuiRender() {}// ����ִ�� ImGui ��Ⱦ���ã������ڵ��Խ���Ĺ�����
		virtual void OnEvent(Event& event) {}// ��������¼���

		inline const std::string& GetName() const { return m_DebugName; }// ���ز�����ƣ����ڵ��Ի���־��¼��
	protected:
		std::string m_DebugName;// �洢�Ų�����ƣ����ڵ��Ե�Ŀ��
	};

}