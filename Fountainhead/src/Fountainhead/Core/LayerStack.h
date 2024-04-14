#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Layer.h"

#include <vector>

namespace Fountainhead {
	//��������һ��Layer�����ķ�װ��
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//ʹ����������Ϊÿһ֡��Ҫ����������Ҳ��Ҫ�����������Ϊ����Ҫ���򴫵��¼������Ƕ���Update������������Ҫ�������
		//֮����û��ʹ��ջ����������Ϊ������Ҫ���м���룬��Ϊ�и���
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }//begin��end�ĵ�����ʵ�֣����ǿ�����App����ʹ��Range-For
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}