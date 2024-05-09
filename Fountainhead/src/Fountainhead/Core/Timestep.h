#pragma once

namespace Fountainhead {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}
		// ���� Timestep ��������Ҫ�����������������Զ�ת��Ϊ float ���ͣ�ֱ�ӷ��ش洢��ʱ��ֵ���룩��
		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }// ����ʱ�䲽��������
		float GetMilliseconds() const { return m_Time * 1000.0f; }// ����ʱ�䲽�ĺ�������ͨ���������� 1000.0f ����ó���
	private:
		float m_Time;
	};

}