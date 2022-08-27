//SoulFire Engine by Ame Gilham, Inspired by The Cherno's Hazel
//Layer.h, class that represents a layer

#pragma once

#include "SoulFire/EngineCore.h"
#include "SoulFire/Events/Event.h"

namespace SoulFire {
	//class that represents a single engine layer
	class SF_API Layer {
	public:
		//constructor
		Layer(const std::string& name = "Layer") { m_Name = name; };
		//destructor
		virtual ~Layer() {};

		//functions called when attaching, detaching, updating, or dispatching events to the layer
		virtual void Attach() {};
		virtual void Detach() {};
		virtual void Update() {};
		virtual void OnEvent(Event& ev) {};
		virtual void ImGuiRender() {};

		//getter for the layer's name
		inline const std::string& GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};
}