//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Entity.cpp - source file for the class that represents entities

#include "SF_PCH.h"
#include "Entity.h"
#include "Components.h"

namespace SoulFire {
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_handle(handle), m_scene(scene)
	{
	}

	std::string& Entity::GetName()
	{
		return GetComponent<InfoComponent>().m_name;
	}
	std::string& Entity::GetTag()
	{
		return GetComponent<InfoComponent>().m_tag;
	}
}