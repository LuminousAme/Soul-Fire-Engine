//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Window.h - header file for the class that represents a soul fire window (implementation will be platform dependent)
#pragma once

#include "SF_PCH.h"
#include "SoulFire/Core/EngineCore.h"
#include "SoulFire/Events/Event.h"
#include "SoulFire/Renderer/GraphicsContext.h"

namespace SoulFire {
	//struct containing general window data like the name and size
	struct WindowDetails {
		//name/title that is displayed at the top of the window
		std::string m_Name;
		//size of the window
		unsigned int m_Width, m_Height;

		//constructor
		WindowDetails(const std::string& name = "Soul Fire Engine", unsigned int width = 1280, unsigned int height = 720) 
			: m_Name(name), m_Width(width), m_Height(height)
		{}
	};

	//abstract window class that the application side will interface with (while the underlying implement will change by platform)
	class SF_API Window {
	public:
		//all functions are virtual to be overloaded by platform implementation

		//destrcutor
		virtual ~Window() {}

		//update tick 
		virtual void Update() = 0;

		//size getters
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual std::pair<unsigned int, unsigned int> GetWindowSize() const = 0;

		//setup event callbacks
		virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
		//set and get wheter or not vsync is enabled
		virtual void SetVSync(bool vysncOn) = 0;
		virtual bool GetVSync() const = 0;

		//function to access the window
		virtual void* GetNativeWindowPointer() const = 0;

		//function to make a new window, 
		static Window* CreateNewWindow(const WindowDetails& details = WindowDetails());

		//clipboard interaction
		virtual const char* GetClipBoardText() = 0;
		virtual void SetClipBoardText(const char* text) = 0;
	};
}