#include "fhpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Fountainhead {

	void OpenGLRendererAPI::Init()// ����OpenGL��һЩ������Ⱦ״̬���Ա�֤��Ⱦ���̵���ȷ�Ժ��Ӿ�Ч����
	{
		FH_PROFILE_FUNCTION();

		glEnable(GL_BLEND);// ���û�ϲ����û�Ϻ������������Ⱦ��͸�������Ǳ�Ҫ�ġ�ʹ�� GL_SRC_ALPHA �� GL_ONE_MINUS_SRC_ALPHA ��Ϊ��ϲ����������ڻ���͸���ȵĵ��ͻ�ϡ�
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);// ������Ȳ�������ȷ����ͼ�ε�ǰ���ϵ����ȷ������ά��Ⱦ�нϽ��������ܹ��ڵ���Զ�����塣
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)// ����OpenGL��Ⱦ�����������������ڴ�������Ⱦ����ľ�������
	{
		glViewport(x, y, width, height);// ���� glViewport �����������ӿڵ�λ�úʹ�С��
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)// ��������ʱʹ�õ���ɫ
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()// �����ɫ����Ȼ�������Ϊ�µ���Ⱦ֡��׼����
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)//  ִ�л��������Ļ��ƣ�����һ�ָ�Ч�Ļ��Ʒ�ʽ���ɼ��ٶ����ظ�������������ܿ�����
	{
		// ʹ�� glDrawElements������OpenGL�����ڻ��������Ļ��Ƶĺ������˺�����Ҫָ������ģʽ�������� GL_TRIANGLES ��ʾÿ������������һ�������Σ��������������������������ͣ������� GL_UNSIGNED_INT�����Լ��������ݵ�λ�ã�����ʹ�� nullptr����Ϊ�����������Ѱ󶨣���
		// vertexArray->GetIndexBuffer()->GetCount() ���û�ȡ�������������������Ҫ��Ⱦ���ٸ�����������ָ���ļ�����״��
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);// �ڻ��ƺ󣬽���κο��ܰ󶨵������Ա��������޸�����״̬��
	}

}