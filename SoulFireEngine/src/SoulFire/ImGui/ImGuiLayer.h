//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//ImGuiLayer.h - header file for the layer that interfaces with ImGui
#pragma once

#include "SoulFire/Layer.h"

#include "SoulFire/Events/KeyEvent.h";
#include "SoulFire/Events/MouseEvent.h";
#include "SoulFire/Events/ApplicationEvent.h"

namespace SoulFire {
	class SF_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void Attach();
		void Detach();
		void Update();
		void OnEvent(Event& ev);
	
	private:
		bool OnKeyPressed(KeyPressedEvent& ev);
		bool OnKeyReleased(KeyReleasedEvent& ev);
		bool OnKeyTyped(KeyTypedEvent& ev);

		bool OnMouseMoved(MouseMovedEvent& ev);
		bool OnMouseScrolled(MouseScrolledEvent& ev);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& ev);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& ev);

		bool OnWindowResize(WindowResizeEvent& ev);

		static const char* GetClipBoardText(void* data);
		static void SetClipBoardText(void* data, const char* text);

	private:
		float m_time = 0.0f;
	};
}