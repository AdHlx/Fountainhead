#include "ExampleLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// ���û��� Layer �Ĺ��캯��������ͼ������� "ExampleLayer"��
// ��ʼ���������������������Ļ��Ϊ1280:720��
ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
{
	// ���ö�������
	// ������Ⱦ��
	// ��������
	m_VertexArray = Fountainhead::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};// ���嶥�����ݣ�����λ�ú���ɫ��Ϣ��

	Fountainhead::Ref<Fountainhead::VertexBuffer> vertexBuffer = Fountainhead::VertexBuffer::Create(vertices, sizeof(vertices));
	Fountainhead::BufferLayout layout = {
		{ Fountainhead::ShaderDataType::Float3, "a_Position" },
		{ Fountainhead::ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Fountainhead::Ref<Fountainhead::IndexBuffer> indexBuffer = Fountainhead::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = Fountainhead::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};// ���������εĶ������ݣ�����λ�ú��������ꡣ

	Fountainhead::Ref<Fountainhead::VertexBuffer> squareVB = Fountainhead::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Fountainhead::ShaderDataType::Float3, "a_Position" },
		{ Fountainhead::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Fountainhead::Ref<Fountainhead::IndexBuffer> squareIB = Fountainhead::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc = R"(
		#version 330 core
			
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)"; // ������ɫ��ʹ�ñ任����u_ViewProjection �� u_Transform����������λ�ñ任���ü��ռ䡣

	std::string fragmentSrc = R"(
		#version 330 core
			
		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;
		}
	)";	// ƬԪ��ɫ�����������ɫֱ�����Ϊ������ɫ��

	m_Shader = Fountainhead::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

	std::string flatColorShaderVertexSrc = R"(
		#version 330 core
			
		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		}
	)";

	std::string flatColorShaderFragmentSrc = R"(
		#version 330 core
			
		layout(location = 0) out vec4 color;

		in vec3 v_Position;

		uniform vec3 u_Color;

		void main()
		{
			color = vec4(u_Color, 1.0);
		}
	)";// ����򻯵�ƬԪ��ɫ��ʹ��ͳһ������uniform����Ϊ��ɫ���룬��ʹ����Ⱦʱ���Զ�̬�ı���ɫ��

	m_FlatColorShader = Fountainhead::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	// ʹ�� ShaderLibrary ���غ͹�����ɫ����
	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = Fountainhead::Texture2D::Create("assets/textures/Checkerboard.png");
	// �����Ͱ�������������Ԫ��
	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Fountainhead::Timestep ts)
{
	// �������
	// ���ñ�����ɫ�������Ļ
	// ��ʼ������Ⱦ
	// ��Ⱦ�����ɫ����Ĵ���
	// ʹ��������ɫ����Ⱦ������
	// ����������Ⱦ
	m_CameraController.OnUpdate(ts);

	Fountainhead::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Fountainhead::RenderCommand::Clear();

	Fountainhead::Renderer::BeginScene(m_CameraController.GetCamera());// ����ʱ�䲽���������״̬����Ӧ�û����롣

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);


	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Fountainhead::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Fountainhead::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Fountainhead::Renderer::EndScene();
}
// �ṩһ��GUI�������ʵʱ�޸ķ������ɫ��
void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
// �����¼����������������
void ExampleLayer::OnEvent(Fountainhead::Event& e)
{
	m_CameraController.OnEvent(e);
}