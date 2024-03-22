#pragma once

#include "Event.h"

namespace Fountainhead {
	class FOUNTAINHEAD_API WindowResizeEvent : public Event//���ڵ�����С�¼�
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }//��ȡ���ڿ�͸�

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent:" << m_Width << "," << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class FOUNTAINHEAD_API WindowCloseEvent : public Event//���ڹر��¼�
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class FOUNTAINHEAD_API AppTickEvent : public Event//֡�¼�
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class FOUNTAINHEAD_API AppUpdateEvent : public Event//�����¼�
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class FOUNTAINHEAD_API AppRenderEvent : public Event//��Ⱦ�¼�
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}