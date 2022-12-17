//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Entity.h - header file for the class that represents entities
#pragma once

#include "Scene.h"
#include "entt.hpp"

namespace SoulFire {

	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			SF_ENGINE_LOG_ASSERT(!HasComponent<T>(), "Entity already has component");
			return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
		}

		template<typename T> 
		void RemoveComponent() {
			SF_ENGINE_LOG_ASSERT(HasComponent<T>(), "Entity does not have component");
			m_scene->m_registry.remove<T>(m_handle);
		}

		template<typename T>
		bool HasComponent() {
			return m_scene->m_registry.has<T>(m_handle);
		}

		template<typename T> 
		T& GetComponent() {
			SF_ENGINE_LOG_ASSERT(HasComponent<T>(), "Entity does not have component");
			return m_scene->m_registry.get<T>(m_handle);
		}

		std::string& GetName();

		std::string& GetTag();

		operator bool() { return m_handle != entt::null; }
		operator uint32_t() { return (uint32_t)m_handle; }

		bool operator==(const Entity& other) const {
			return m_handle == other.m_handle && m_scene == other.m_scene;
		}
		bool operator!=(const Entity& other) const {
			return !(*this == other);
		}
	private:
		entt::entity m_handle = entt::null;
		Scene* m_scene = nullptr;
	};
}