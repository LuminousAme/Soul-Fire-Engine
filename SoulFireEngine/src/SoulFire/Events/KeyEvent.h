//SoulFire Engine by Ame Gilham, inspired by The Cherno's Hazel
//KeyEvent.h - class for keyboard events

#pragma once

#include "Event.h"

namespace SoulFire {
	//class for key events in general
	class SF_API KeyEvent : public Event {
	public:
		//getter for the keycode
	 int GetKeyCode() const { return m_KeyCode; }

		//event type
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		//construtor
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode) {}

		int m_KeyCode;
	};

	//class for the key pressed
	class SF_API KeyPressedEvent : public KeyEvent
	{
	public:
		//constructor, makes a keyevent with the keycode, and saves the number of repeats
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount) {}

		//getter for the number of repeats
		inline int GetRepeatCount() const { return m_repeatCount; }

		//ToString override that will spit out a string with the keycode and the number of times it has been repeated
		std::string ToString() const override
		{
			std::stringstream ss; 
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		//save the class type as keypressed
		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int m_repeatCount;
	};

	//class for key released
	class SF_API KeyReleasedEvent : public KeyEvent
	{
	public:
		//constructor, makes a keyevent with the keycode
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		//ToString override that will spit out a string with the keycode
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		//save the class type as keyrealeased
		EVENT_CLASS_TYPE(KeyReleased);
	};
}