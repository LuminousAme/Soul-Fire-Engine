//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//WindowsWindow.h - header file for soul fire windows on the Microsoft windows platform
#pragma once

#include "SoulFire/Window.h"
#include "GLFW/glfw3.h"

namespace SoulFire {
	//definition of the window class for the micrcosoft windows platform
	class WindowsWindow : public Window
	{
	public:
		//constructor
		WindowsWindow(const WindowDetails& details);
		//destructor
		virtual ~WindowsWindow();

		//update tick 
		void Update() override;

		//getters for window width and height
		inline unsigned int GetWidth() const override { return m_data.m_width; }
		inline unsigned int GetHeight() const override { return m_data.m_height; }

		//sets the event callback function
		inline void SetEventCallback(const std::function<void(Event&)>& callback) override { m_data.EventCallback = callback; };

		//getter and setter for vsync
		void SetVSync(bool vysncOn) override;
		bool GetVSync() const override;

	private:
		//function for startup and shutdown
		virtual void Startup(const WindowDetails& details);
		virtual void Shutdown();

	private:
		//pointer to the glfw window
		GLFWwindow* m_window;

		//struct with window data that can be passed to glfw as custom user data without needing to send the entire window class
		struct WindowData {
			std::string m_title;
			unsigned int m_width, m_height;

			bool vysnc;

			std::function<void(Event&)> EventCallback;
		};

		//object of that struct since we do need the data around here
		WindowData m_data;
	};
}