//SoulFire Engine by Ame Gilham, inspired by The Cherno's Hazel
//MouseEvent.h - class for mouse events

#pragma once

#include "Event.h"

namespace SoulFire {
	//mouse moved event class
	class SF_API MouseMovedEvent : public Event
	{
	public:
		//constructor, takes the new x and y
		MouseMovedEvent(const float x, const float y)
			: m_mouseX(x), m_mouseY(y) {}

		//getters for the mouse position
		float GetX() const { return m_mouseX; }
		float GetY() const { return m_mouseY; }

		//To String override for logging
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		//setting class type and category for the event
		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		//mouse position
		float m_mouseX, m_mouseY;
	};

	//mouse scrolled event class
	class SF_API MouseScrolledEvent : public Event
	{
	public:
		//constructor, takes the new x and y
		MouseScrolledEvent(const float x, const float y)
			: m_offsetX(x), m_offsetY(y) {}

		//getters for the mouse position
		float GetOffsetX() const { return m_offsetX; }
		float GetOffsetY() const { return m_offsetY; }

		//To String override for logging
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_offsetX << ", " << m_offsetY;
			return ss.str();
		}

		//setting class type and category for the event
		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		//mouse position
		float m_offsetX, m_offsetY;
	};

	//mouse button event
	class SF_API MouseButtonEvent : public Event {
	public:
		//getter for the code
		int GetMouseButtonCode() const { return m_MBcode; }

		//event type
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput )
	protected:
		//construtor
		MouseButtonEvent(int mouseButtonCode)
			: m_MBcode(mouseButtonCode) {}

		//code for which button has been pressed
		int m_MBcode;
	};

	//class for the mouse button pressed
	class SF_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		//constructor, makes a mousebuttonevent with the code
		MouseButtonPressedEvent(int code)
			: MouseButtonEvent(code) {}

		//ToString override that will spit out a string with the code
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_MBcode;
			return ss.str();
		}

		//save the class type as keypressed
		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	//class for the mouse button released
	class SF_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		//constructor, makes a mousebuttonevent with the code
		MouseButtonReleasedEvent(int code)
			: MouseButtonEvent(code) {}

		//ToString override that will spit out a string with the code
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_MBcode;
			return ss.str();
		}

		//save the class type as keypressed
		EVENT_CLASS_TYPE(MouseButtonReleased);
	};
}