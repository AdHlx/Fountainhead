#pragma once

#include <memory>
#include "Buffer.h"

namespace Fountainhead {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;// 绑定顶点数组对象到当前的渲染上下文。这是在进行绘图调用前准备顶点输入数据的标准步骤。
		virtual void Unbind() const = 0;// 解绑顶点数组对象，以便其他顶点数组可以被绑定和使用。这有助于管理渲染上下文状态，避免渲染错误。

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;// 将一个顶点缓冲区添加到顶点数组中。这允许顶点数组管理多个顶点缓冲区，每个顶点缓冲区可以包含不同种类的顶点数据。
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;// 设置索引缓冲区。索引缓冲区用于定义顶点的索引，可以有效地重用顶点数据，优化内存使用和渲染性能。

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;// 返回与顶点数组关联的所有顶点缓冲区的引用列表。这允许外部访问和检查已添加的顶点缓冲区。
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;// 返回当前设置的索引缓冲区的引用。这提供了一种检索顶点数组当前使用的索引缓冲区的方式。

		static Ref<VertexArray> Create();// 创建一个顶点数组实例。这是一个工厂方法，它根据实际的渲染API创建适当类型的 VertexArray 对象。例如，在使用OpenGL时，它会创建一个特定于OpenGL的 VertexArray 实现。
	};

}