#pragma once

#include "Fountainhead/Core.h"
#include "Layer.h"

#include <vector>

namespace Fountainhead {
	//基本上是一个Layer向量的封装器
	class FOUNTAINHEAD_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//使用向量是因为每一帧都要遍历，而且也需要反向迭代，因为我们要反向传递事件，但是对于Update，我们总是需要正向遍历
		//之所以没有使用栈容器，是因为我们需要向中间插入，因为有覆层
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }//begin和end的迭代器实现，我们可以在App类中使用Range-For
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}