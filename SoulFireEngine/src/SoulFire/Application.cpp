//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Application.cpp - source file for the class that represnets a Soul Fire Application

//precompile header
#include "SF_PCH.h"

#include "Application.h"

//include logging
#include "Logger.h"

namespace SoulFire {
	Application::Application()
	{
		//create a new window
		m_window = std::unique_ptr<Window>(Window::CreateNewWindow());
		//sets the callback so that when the window sends an event, the OnEvent function is called
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& ev) {
		//make a dispatcher
		EventDispatcher dispatcher(ev);
		//check if it's a window close event and if it is, run the window close function
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		//for now just print that an event has occured
		SF_ENGINE_LOG_TRACE("{0}", ev);
	}

	void Application::Run()
	{
		//while the application is running
		while (m_running) {
			m_window->Update();
		}
	}


	//when the window close event is dispatched
	bool Application::OnWindowClose(WindowCloseEvent& ev)
	{
		//set the application running to false
		m_running = false;
		//and the event handled is true
		return true;
	}
}