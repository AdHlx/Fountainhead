#include "fhpch.h"
#include "LayerStack.h"

namespace Fountainhead {
	//一旦把层交给层栈，就被层栈所有，所以当把层指针推给层栈时，层栈把层推入到正确的位置
	//当层栈销毁时，层都被释放
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
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);//层被推入列表前半部分
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);//覆层被推入列表后半部分
	}
	//弹出层时不会被释放，只有销毁层时才会，层栈的所有权是应用程序(Application)，这意味着可以分配层，只要把层传给层栈并且不弹出层，层就会在程序关闭时释放
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