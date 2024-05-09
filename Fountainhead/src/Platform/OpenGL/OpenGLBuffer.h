#pragma once

#include "Fountainhead/Renderer/Buffer.h"

namespace Fountainhead {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);// 接收一组顶点数据和数据大小，用来创建一个OpenGL顶点缓冲区（VBO）。顶点数据被上传到GPU，用于图形渲染。
		virtual ~OpenGLVertexBuffer();// 析构函数负责在对象生命周期结束时释放OpenGL缓冲区资源。

		virtual void Bind() const override;// 将此顶点缓冲区绑定到当前的OpenGL上下文中，使其成为当前活动的顶点缓冲区，随后的顶点绘制操作将使用这里的数据。
		virtual void Unbind() const override;// 解绑当前顶点缓冲区，确保后续操作不会意外改变这个缓冲区的内容。

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }// 返回顶点缓冲区的布局（BufferLayout），这定义了顶点数据的组织结构，如每个顶点的数据类型和顺序。
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }// 设置顶点缓冲区的布局，这允许用户定义顶点属性如位置、颜色、法线等信息的存储方式。
	private:
		uint32_t m_RendererID;// OpenGL分配的唯一标识符，用于引用特定的顶点缓冲区。
		BufferLayout m_Layout;// 描述顶点数据布局的 BufferLayout 对象。
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);// 接收索引数据和索引数量，创建一个OpenGL索引缓冲区（IBO）。索引数据用于定义顶点数组中哪些顶点按照特定顺序组成图形的基元，如三角形。
		virtual ~OpenGLIndexBuffer();// 析构函数负责释放索引缓冲区资源。
		// 分别用于绑定和解绑索引缓冲区。绑定后，绘制调用将使用这些索引来确定如何从顶点缓冲区中提取顶点。
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }// 返回索引的数量，这是图形绘制命令在使用索引缓冲区时需要的信息，以确定要渲染的图元数目。
	private:
		uint32_t m_RendererID;// 与顶点缓冲区类似，这是OpenGL为索引缓冲区分配的唯一标识符。
		uint32_t m_Count;// 存储索引的数量，表示索引缓冲区中包含多少索引。
	};

}