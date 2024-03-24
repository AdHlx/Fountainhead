#include "fhpch.h"
#include "LayerStack.h"

namespace Fountainhead {
	//һ���Ѳ㽻����ջ���ͱ���ջ���У����Ե��Ѳ�ָ���Ƹ���ջʱ����ջ�Ѳ����뵽��ȷ��λ��
	//����ջ����ʱ���㶼���ͷ�
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);//�㱻�����б�ǰ�벿��
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);//���㱻�����б��벿��
	}
	//������ʱ���ᱻ�ͷţ�ֻ�����ٲ�ʱ�Żᣬ��ջ������Ȩ��Ӧ�ó���(Application)������ζ�ſ��Է���㣬ֻҪ�Ѳ㴫����ջ���Ҳ������㣬��ͻ��ڳ���ر�ʱ�ͷ�
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}