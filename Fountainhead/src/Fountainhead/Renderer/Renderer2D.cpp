#include "fhpch.h"
#include "Fountainhead/Renderer/Renderer2D.h"

#include "Fountainhead/Renderer/VertexArray.h"
#include "Fountainhead/Renderer/Shader.h"
#include "Fountainhead/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Fountainhead {
	// 存储了渲染器2D相关的数据，包括顶点数组、着色器和纹理。
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};
	// 存储了 Renderer2DStorage 结构体的实例。
	static Renderer2DStorage* s_Data;
	// 初始化函数，用于初始化渲染器2D。
	void Renderer2D::Init()
	{
		FH_PROFILE_FUNCTION();
		// 创建了顶点数组和顶点缓冲对象，用于绘制矩形。
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
		// 创建了一个白色的纹理，并设置了纹理数据。
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		// 创建了着色器程序，并设置了纹理采样器的值。
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}
	// 关闭函数，用于关闭渲染器2D。
	void Renderer2D::Shutdown()
	{
		FH_PROFILE_FUNCTION();

		delete s_Data;
	}
	// 开始渲染场景，绑定着色器并设置视图投影矩阵。
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		FH_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	// 结束渲染场景。
	void Renderer2D::EndScene()
	{
		FH_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		FH_PROFILE_FUNCTION();
		// 设置着色器中的颜色或纹理。
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();
		// 计算变换矩阵并设置给着色器。
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		// 绑定顶点数组并使用渲染命令进行绘制。
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		FH_PROFILE_FUNCTION();
		// 设置着色器中的颜色或纹理。
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();
		// 计算变换矩阵并设置给着色器。
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		// 绑定顶点数组并使用渲染命令进行绘制。
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}