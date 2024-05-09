#pragma once

#include <string>

#include "Fountainhead/Core/Core.h"

namespace Fountainhead {

	class Texture
	{
	public:
		virtual ~Texture() = default;
		// 返回纹理的宽度和高度。
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		// 设置纹理的数据。这是用于动态更新纹理内容的重要功能，比如更新纹理的一部分（如纹理地图的一块区域）。
		virtual void SetData(void* data, uint32_t size) = 0;
		// 将纹理绑定到指定的纹理单元。这允许在着色器中使用多个纹理。
		virtual void Bind(uint32_t slot = 0) const = 0;
	};
	// Texture 的具体实现，专门用于处理二维图像数据。
	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);// 创建一个指定宽高的空白二维纹理。这通常用于动态纹理生成，如渲染到纹理（Render-to-Texture, RTT）操作。
		static Ref<Texture2D> Create(const std::string& path);// 从文件路径加载一个二维纹理。这是常见的纹理加载方法，用于从图像文件创建纹理。
	};

}