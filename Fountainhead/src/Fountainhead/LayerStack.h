#pragma once

#include "Fountainhead/Core.h"
#include "Layer.h"

#include <vector>

namespace Fountainhead {
	//��������һ��Layer�����ķ�װ��
	class FOUNTAINHEAD_API LayerStack
	{
	public:
		LayerStack();
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
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}