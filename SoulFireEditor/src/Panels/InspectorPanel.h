//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//InspectorPanel.h - header file for the class that represents the panel to view the components of an entity
#pragma once

#include "SceneHierarchyPanel.h"

namespace SoulFire {
	class InspectorPanel {
	public:
		InspectorPanel() = default;

		void OnImGuiRender(SceneHierarchyPanel& hierarchyPanel);

	private:
		void DrawComponents(Entity entity);
	};
}