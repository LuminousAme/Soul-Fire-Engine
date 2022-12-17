//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneHierarchyPanel.h - header file for the class that represents the scenegraph
#pragma once

#include "SoulFire.h"

namespace SoulFire {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const sptr<Scene>& scene);

		void SetContext(const sptr<Scene>& scene);

		void OnImguiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		sptr<Scene> m_context = nullptr;
		Entity m_selectionContext = Entity();

		friend class InspectorPanel;
	};
}