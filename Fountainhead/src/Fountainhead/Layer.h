#pragma once

#include "Fountainhead/Core.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	class FOUNTAINHEAD_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}//��������ջ����Ϊ�����һ����ʱ����Attached(����)
		virtual void OnDetach() {}//���㱻�Ƴ�ʱ��Detach(����)
		virtual void OnUpdate() {}//�ڲ����ʱ��Ӧ�ó�����ã�Ӧ��ÿ֡����һ��
		virtual void OnEvent(Event& event) {}//��õ��¼�ʱ�����Ǵ��������

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}