#include "fhpch.h"
#include "Fountainhead/Core/LayerStack.h"

namespace Fountainhead {
	//一旦把层交给层栈，就被层栈所有，所以当把层指针推给层栈时，层栈把层推入到正确的位置
	//当层栈销毁时，层都被释放

	LayerStack::~LayerStack()// 遍历 m_Layers 向量，对每个 Layer* 调用 OnDetach() 方法后执行 delete，以释放内存。
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);// 使用 std::vector::emplace 在 m_Layers.begin() + m_LayerInsertIndex 位置插入新层，该位置是图层和覆盖层的分界点。
		m_LayerInsertIndex++;// 每插入一个图层，m_LayerInsertIndex 自增以更新新的插入点位置。
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);// 使用 std::vector::emplace_back 直接在向量尾部添加新覆盖层，因为覆盖层总是位于所有常规图层之上。
	}
	// 弹出层时不会被释放，只有销毁层时才会，层栈的所有权是应用程序(Application)，这意味着可以分配层，只要把层传给层栈并且不弹出层，层就会在程序关闭时释放
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);// 使用 std::find 从 m_Layers 的开始到 m_LayerInsertIndex 查找指定的图层。
		if (it != m_Layers.begin() + m_LayerInsertIndex)// 如果找到，调用 OnDetach()，从列表中移除，并递减 m_LayerInsertIndex。
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);// 使用 std::find 从 m_Layers 的 m_LayerInsertIndex 到结束查找指定的覆盖层。
		if (it != m_Layers.end())// 如果找到，调用 OnDetach()，从列表中移除。
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}