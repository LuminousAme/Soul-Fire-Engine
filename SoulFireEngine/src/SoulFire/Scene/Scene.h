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
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = std::string());
		void Destroy(Entity entity);

		static sptr<Scene> Create() { return std::make_shared<Scene>(); }
	private:

	private:
		entt::registry m_registry;
		uint32_t m_viewportWidth = 0, m_viewportHeight = 0;
		std::vector<Entity> newCameraEntities;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}