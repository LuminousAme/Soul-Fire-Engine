//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Application.h - header file for the class that represnets a Soul Fire Application
#pragma once

#include "EngineCore.h"
#include "Window.h"
#include "LayerTree.h"

//include all of the different event files
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace SoulFire {
	class SF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& ev);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& GetApp() { return *s_Instance; };
		inline Window& GetWindow() { return *m_window; };

	private:
		bool OnWindowClose(WindowCloseEvent& ev);

	private:
		//the window
		std::unique_ptr<Window> m_window;
		//wheter or not the application is running
		bool m_running = true;

		//the layerstack
		LayerTree m_layerTree;

	private:
		//singleton
		static Application* s_Instance;
	};

	// To be defined by client
	Application* CreateApplication();
}