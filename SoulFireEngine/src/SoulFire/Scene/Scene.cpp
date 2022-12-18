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
		newCameraEntities = std::vector<Entity>();
	}

	Scene::~Scene()
	{
	}

	void Scene::Update()
	{
		for (uint32_t i = 0; i < newCameraEntities.size(); i++) {
			if (!newCameraEntities[i].HasComponent<CameraComponent>()) continue;

			CameraComponent& cam = newCameraEntities[i].GetComponent<CameraComponent>();
			cam.camera.SetViewportSize(m_viewportWidth, m_viewportHeight);
		}
		newCameraEntities.clear();

		//Render 2D
		RuntimeCamera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		auto camGroup = m_registry.group<CameraComponent>(entt::get<Transform>);
		for (auto entity : camGroup) {
			auto& [cam, trans] = camGroup.get<CameraComponent, Transform>(entity);

			if (cam.main) {
				mainCamera = &cam.camera;
				cameraTransform = &trans.GetTransform();
				break;
			}
		}

		if (mainCamera) {
			Renderer2D::BeginRenderPass(*mainCamera, *cameraTransform);

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

			Renderer2D::EndRenderPass();
		}

	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_viewportWidth = width;
		m_viewportHeight = height;

		//resize cameras that don't have a fixed aspect ratio
		auto view = m_registry.view<CameraComponent>();
		for (auto entity : view) {
			CameraComponent& cam = view.get<CameraComponent>(entity);
			if (!cam.fixedAspectRatio) {
				cam.camera.SetViewportSize(width, height);
			}
		}
	}

	Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
	{
		Entity entity = Entity(m_registry.create(), this);
		entity.AddComponent<Transform>();
		entity.AddComponent<InfoComponent>(name, tag);
		return entity;
	}

	void Scene::Destroy(Entity entity)
	{
		m_registry.destroy(entity);
	}
}
