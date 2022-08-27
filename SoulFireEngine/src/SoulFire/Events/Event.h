//SoulFire Engine by Ame Gilham, inspired by The Cherno's Hazel
//Event.h - base event handling class

#pragma once

#include "SoulFire/EngineCore.h"

namespace SoulFire {
	//events are currently blocking so they are executed as soon as they callback, no queuing

	//an enum class for different types of events
	enum class EventType
	{
		None = 0, 
		WindowClose, 
		WindowResize, 
		WindowFocus, 
		WindowUnFocus, 
		WindowMove,
		AppTick, 
		AppUpdate, 
		AppRender,
		KeyPressed, 
		KeyReleased,
		KeyTyped,
		MouseButtonPressed, 
		MouseButtonReleased, 
		MouseMoved, 
		MouseScrolled
	};

	//different categories of events so we can filter them
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = (1 << 0),
		EventCategoryInput = (1 << 1),
		EventCategoryKeyboard = (1 << 2),
		EventCategoryMouse = (1 << 3),
		EventCategoryMouseButton = (1 << 4)
	};

//macros to override the GetEventType, GetEventName, and GetEventCategoryFlag 
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetEventName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

	//the base class for events
	class SF_API Event {
		//allow the dispatcher to access the private and protected data of events
		friend class EventDispatcher;
	public:
		//getters for various data in the events
		virtual EventType GetEventType() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual int GetEventCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetEventName(); }

		//checks if the event is of a given category
		inline bool IsOfCategory(EventCategory category) {
			return GetEventCategoryFlags() & category;
		}

		//gets wheter or not the event has been handled
		inline bool GetHandled() const { return m_handled; }

	protected:
		//boolean for if an event has been handled
		bool m_handled = false;
	};


	//class to dispatch any event based on their type
	class EventDispatcher {
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		//constructor, saves an event from it's reference
		EventDispatcher(Event& event)
			: m_Event(event) {}

		//verifies the event type saved in the dispatcher and the function trying to handle it are for the same event type
		//if they, it calls the function and saves the result to wheter or not the event was handled, if not it just doesn't
		//either way it returns if it did or not
		template<typename T>
		bool Dispatch(EventFunc<T> func) {
			//verify event type
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//call the function to handle that event and store the boolean it spits out in the event's handled field
				m_Event.m_handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		//the event to be dispatched, we make a new dispatcher object for each event
		Event& m_Event;
	};

	//output string operator to help make logging easier 
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}