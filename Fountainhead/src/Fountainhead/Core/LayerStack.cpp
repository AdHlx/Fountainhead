#include "fhpch.h"
#include "Fountainhead/Core/LayerStack.h"

namespace Fountainhead {
	//һ���Ѳ㽻����ջ���ͱ���ջ���У����Ե��Ѳ�ָ���Ƹ���ջʱ����ջ�Ѳ����뵽��ȷ��λ��
	//����ջ����ʱ���㶼���ͷ�

	LayerStack::~LayerStack()// ���� m_Layers ��������ÿ�� Layer* ���� OnDetach() ������ִ�� delete�����ͷ��ڴ档
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);// ʹ�� std::vector::emplace �� m_Layers.begin() + m_LayerInsertIndex λ�ò����²㣬��λ����ͼ��͸��ǲ�ķֽ�㡣
		m_LayerInsertIndex++;// ÿ����һ��ͼ�㣬m_LayerInsertIndex �����Ը����µĲ����λ�á�
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);// ʹ�� std::vector::emplace_back ֱ��������β������¸��ǲ㣬��Ϊ���ǲ�����λ�����г���ͼ��֮�ϡ�
	}
	// ������ʱ���ᱻ�ͷţ�ֻ�����ٲ�ʱ�Żᣬ��ջ������Ȩ��Ӧ�ó���(Application)������ζ�ſ��Է���㣬ֻҪ�Ѳ㴫����ջ���Ҳ������㣬��ͻ��ڳ���ر�ʱ�ͷ�
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);// ʹ�� std::find �� m_Layers �Ŀ�ʼ�� m_LayerInsertIndex ����ָ����ͼ�㡣
		if (it != m_Layers.begin() + m_LayerInsertIndex)// ����ҵ������� OnDetach()�����б����Ƴ������ݼ� m_LayerInsertIndex��
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);// ʹ�� std::find �� m_Layers �� m_LayerInsertIndex ����������ָ���ĸ��ǲ㡣
		if (it != m_Layers.end())// ����ҵ������� OnDetach()�����б����Ƴ���
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}