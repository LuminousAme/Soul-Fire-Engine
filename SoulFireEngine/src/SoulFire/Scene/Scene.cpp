//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Scene.cpp - source file for the class that represents scenes and wraps around entt

#include "SF_PCH.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "SoulFire/Renderer/Renderer2D.h"
#include "SoulFire/Renderer/Texture.h"

namespace SoulFire {


	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Update()
	{
		auto transspritegroup = m_registry.group<Transform>(entt::get<SpriteRenderer>);
		for (auto entity : transspritegroup) {
			auto& [trans, sprite] = transspritegroup.get<Transform, SpriteRenderer>(entity);
			if (sprite.m_subsprite != nullptr) {
				TextureProps props = TextureProps();
				props.tint = sprite.m_color;
				props.tilingFactor = sprite.m_tilingFactor;
				Renderer2D::DrawQuad(trans.GetTransform(), sprite.m_subsprite, props);
			}
			else if (sprite.m_fullsprite != nullptr) {
				TextureProps props = TextureProps();
				props.tint = sprite.m_color;
				props.tilingFactor = sprite.m_tilingFactor;
				Renderer2D::DrawQuad(trans.GetTransform(), sprite.m_fullsprite, props);
			}
			else Renderer2D::DrawQuad(trans.GetTransform(), sprite.m_color);
		}
	}

	Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
	{
		Entity entity = Entity(m_registry.create(), this);
		entity.AddComponent<Transform>();
		entity.AddComponent<InfoComponent>(name, tag);
		return entity;
	}
}
