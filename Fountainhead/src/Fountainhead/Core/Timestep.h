#pragma once

namespace Fountainhead {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}
		// 允许 Timestep 对象在需要浮点数的上下文中自动转换为 float 类型，直接返回存储的时间值（秒）。
		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }// 返回时间步的秒数。
		float GetMilliseconds() const { return m_Time * 1000.0f; }// 返回时间步的毫秒数，通过秒数乘以 1000.0f 计算得出。
	private:
		float m_Time;
	};

}