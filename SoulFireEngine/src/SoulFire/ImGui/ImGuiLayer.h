//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//ImGuiLayer.h - header file for the layer that interfaces with ImGui
#pragma once

#include "SoulFire/Core/Layer.h"

#include "SoulFire/Events/ApplicationEvent.h"
#include "SoulFire/Events/KeyEvent.h"
#include "SoulFire/Events/MouseEvent.h"

namespace SoulFire {
	class SF_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void Attach() override;
		void Detach() override;
		void ImGuiRender() override;

		void OnEvent(Event& ev) override;
	
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
		void SetLightThemeColors();
	private:
		bool BlockEventFunc(Event& ev);
	private:
		bool m_BlockEvents = true;
		float m_time = 0.0f;
	};
}