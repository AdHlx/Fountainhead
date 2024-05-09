#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Layer.h"

#include <vector>

namespace Fountainhead {
	// ��������һ��Layer�����ķ�װ��
	class LayerStack
	{
	public:
		LayerStack() = default;// Ĭ�Ϲ��캯������ʼ��һ���յ�ͼ��ջ��
		~LayerStack();// �����������е�ͼ�㣬ȷ��ÿ��ͼ��� OnDetach ���������ã�Ȼ��ɾ��ͼ�����

		void PushLayer(Layer* layer);// ��һ��ͼ������ջ�У����ڸ��ǲ�֮ǰ��
		void PushOverlay(Layer* overlay);// ��һ�����ǲ��Ƶ�ջ�Ķ�����
		void PopLayer(Layer* layer);// �Ƴ�һ��ָ����ͼ�㡣
		void PopOverlay(Layer* overlay);// �Ƴ�һ��ָ���ĸ��ǲ㡣
		// ��׼�ͷ���������ķ��ʷ�����begin, end, rbegin, rend����ʹ���ⲿ�������ͨ�����������ʺ��޸Ĳ�ջ�е�ͼ�㡣
		// ʹ����������Ϊÿһ֡��Ҫ����������Ҳ��Ҫ�����������Ϊ����Ҫ���򴫵��¼������Ƕ���Update������������Ҫ�������
		// ֮����û��ʹ��ջ����������Ϊ������Ҫ���м���룬��Ϊ�и���
		// begin��end�ĵ�����ʵ�֣����ǿ�����App����ʹ��Range-For���ṩ��ͬ��������ݷ��ʱ�����ȷ���ڲ���Ҫ�޸����ݵ��龳�з�ֹ����������޸ġ�
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
		// ����Ҫ��ȡ
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;// һ���������洢��ջ�е�����ͼ��ָ��
		unsigned int m_LayerInsertIndex = 0;// һ�����������ڼ�¼��ͨ������λ�ã�ȷ�����ǲ�����λ��ջ����
	};
}