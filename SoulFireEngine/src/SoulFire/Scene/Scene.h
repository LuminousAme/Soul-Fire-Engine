//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Scene.h - header file for the class that represents scenes and wraps around entt
#pragma once

#include "SF_PCH.h"
#include "entt.hpp"


namespace SoulFire {
	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();

		void Update();

		Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = std::string());

		static sptr<Scene> Create() { return std::make_shared<Scene>(); }
	private:
		entt::registry m_registry;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}