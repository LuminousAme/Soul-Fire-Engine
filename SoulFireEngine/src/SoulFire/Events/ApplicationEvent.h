//SoulFire Engine by Ame Gilham, inspired by The Cherno's Hazel
//ApplicationEvent.h - classes for application events

#pragma once

#include "Event.h"

namespace SoulFire {
	//class for the event of a window resize
	class WindowResizeEvent : public Event
	{
	public:
		//constructor, takes the new width and height of the screen
		WindowResizeEvent(unsigned int width, unsigned int height) 
		: m_Width(width), m_Height(height) {}
	
		//getters for the window size
		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		//to string override for logging
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		//classifiying event type
		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		//new size of the window
		unsigned int m_Width, m_Height;
	};

	//class for the event of a window closing
	class WindowCloseEvent : public Event
	{
	public:
		//default constructor as we don't need to store any data here
		WindowCloseEvent() = default;

		//classifying the event type
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	//class for the application ticking and update
	class AppTickEvent : public Event
	{
	public:
		//default constructor as we don't need to save any data for this
		AppTickEvent() = default;

		//classifying event type
		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	//class for the application updating
	class AppUpdateEvent : public Event
	{
	public:
		//default constructor as we don't need any data
		AppUpdateEvent() = default;

		//classifying event type
		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	//class for the application rendering
	class AppRenderEvent : public Event
	{
	public:
		//default constructor as we don't need any data
		AppRenderEvent() = default;

		//classifying event type
		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}