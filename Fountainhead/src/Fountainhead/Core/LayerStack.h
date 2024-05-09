#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Layer.h"

#include <vector>

namespace Fountainhead {
	// 基本上是一个Layer向量的封装器
	class LayerStack
	{
	public:
		LayerStack() = default;// 默认构造函数，初始化一个空的图层栈。
		~LayerStack();// 负责清理所有的图层，确保每个图层的 OnDetach 方法被调用，然后删除图层对象。

		void PushLayer(Layer* layer);// 将一个图层推入栈中，但在覆盖层之前。
		void PushOverlay(Layer* overlay);// 将一个覆盖层推到栈的顶部。
		void PopLayer(Layer* layer);// 移除一个指定的图层。
		void PopOverlay(Layer* overlay);// 移除一个指定的覆盖层。
		// 标准和反向迭代器的访问方法（begin, end, rbegin, rend），使得外部代码可以通过迭代器访问和修改层栈中的图层。
		// 使用向量是因为每一帧都要遍历，而且也需要反向迭代，因为我们要反向传递事件，但是对于Update，我们总是需要正向遍历
		// 之所以没有使用栈容器，是因为我们需要向中间插入，因为有覆层
		// begin和end的迭代器实现，我们可以在App类中使用Range-For，提供不同级别的数据访问保护，确保在不需要修改数据的情境中防止意外的数据修改。
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
		// 仅需要读取
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;// 一个向量，存储了栈中的所有图层指针
		unsigned int m_LayerInsertIndex = 0;// 一个索引，用于记录普通层插入的位置，确保覆盖层总是位于栈顶。
	};
}