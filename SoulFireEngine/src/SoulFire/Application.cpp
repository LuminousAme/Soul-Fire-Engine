//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Application.cpp - source file for the class that represnets a Soul Fire Application

//precompile header
#include "SF_PCH.h"

#include "Application.h"

//include logging
#include "Logger.h"

#include "Input.h"

namespace SoulFire {

	Application* Application::s_Instance = nullptr; 

	Application::Application()
	{
		//save the singleton
		s_Instance = this;

		//create a new window
		m_window = std::unique_ptr<Window>(Window::CreateNewWindow());
		//sets the callback so that when the window sends an event, the OnEvent function is called
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_imguiLayer = new ImGuiLayer();
		PushOverlay(m_imguiLayer);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& ev) {
		//make a dispatcher
		EventDispatcher dispatcher(ev);
		//check if it's a window close event and if it is, run the window close function
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		//send the events through the layers in reverse order until one of them handles the event
		for (auto it = m_layerTree.end(); it != m_layerTree.begin();) {
			//dispatch the event
			(*--it)->OnEvent(ev);
			//if it is handled after being dispatched stop handing it off
			if (ev.GetHandled()) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerTree.PushLayer(layer);
		layer->Attach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerTree.PushOverlay(overlay);
		overlay->Attach();
	}

	void Application::Run()
	{
		//while the application is running
		while (m_running) {
			//update all of the layers
			for (Layer* layer : m_layerTree) layer->Update();

			//begin imgui
			m_imguiLayer->Begin();

			//render imgui for each layer
			for (Layer* layer : m_layerTree) layer->ImGuiRender();

			//end imgui 
			m_imguiLayer->End();

			//update the window
			m_window->Update();

			//reset the keys at the end of the frame
			Input::ResetInput();
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