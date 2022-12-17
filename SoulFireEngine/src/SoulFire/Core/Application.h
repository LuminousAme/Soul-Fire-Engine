//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Application.h - header file for the class that represnets a Soul Fire Application
#pragma once

#include "EngineCore.h"
#include "Window.h"
#include "LayerTree.h"

//include all of the different event files
#include "SoulFire/Events/Event.h"
#include "SoulFire/Events/ApplicationEvent.h"
#include "SoulFire/Events/MouseEvent.h"
#include "SoulFire/Events/KeyEvent.h"

//include the imgui layer
#include "SoulFire/ImGui/ImGuiLayer.h"

//include graphics stuff
#include "SoulFire/Renderer/Shader.h"
#include "SoulFire/Renderer/Buffer.h"
#include "SoulFire/Renderer/VertexArrayObject.h"

//time 
#include "SoulFire/Core/Time.h"

namespace SoulFire {
	class SF_API Application
	{
	public:
		Application(const std::string& name = "Soul Fire Engine");
		virtual ~Application();

		void Run();

		void Close();

		void OnEvent(Event& ev);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		ImGuiLayer* GetImGuiLayer() { return m_imguiLayer; }

		inline static Application& GetApp() { return *s_Instance; };
		inline Window& GetWindow() { return *m_window; };

	private:
		bool OnWindowClose(WindowCloseEvent& ev);
		bool OnWindowResize(WindowResizeEvent& ev);

	private:
		//the window
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imguiLayer;
		//wheter or not the application is running
		bool m_running = true;
		bool m_minimized = false;

		//the layerstack
		LayerTree m_layerTree;

	private:
		//singleton
		static Application* s_Instance;
	};

	// To be defined by client
	Application* CreateApplication();
}