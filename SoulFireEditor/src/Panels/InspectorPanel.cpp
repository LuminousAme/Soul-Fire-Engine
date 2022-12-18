//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//InspectorPanel.cpp - source file for the class that represents the panel to view the components of an entity

#include "InspectorPanel.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "glm/gtc/type_ptr.hpp"
#include "SoulFire/ImGui/ImGuiFields.h"

namespace SoulFire {
	void InspectorPanel::OnImGuiRender(SceneHierarchyPanel& hierarchyPanel)
	{
		ImGui::Begin("Inspector");
		DrawComponents(hierarchyPanel.m_selectionContext);
		if (ImGuiFields::CentreAlignedButton("Add Component", {100.0f, 20.0f})) ImGui::OpenPopup("AddComponent");
		if (ImGui::BeginPopup("AddComponent")) {
			if (ImGui::MenuItem("Camera")) {
				hierarchyPanel.m_selectionContext.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Sprite Renderer")) {
				hierarchyPanel.m_selectionContext.AddComponent<SpriteRenderer>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		ImGui::End();
	}

	void InspectorPanel::DrawComponents(Entity entity)
	{
		if (entity) {
			//Info Component
			if (entity.HasComponent<InfoComponent>()) {
				if (ImGui::TreeNodeEx((void*)typeid(InfoComponent).hash_code(),ImGuiTreeNodeFlags_DefaultOpen, "Entity")) {
					std::string& name = entity.GetComponent<InfoComponent>().m_name;
					ImGuiFields::ShortTextField("EntityName", "Name", name);
					ImGui::TreePop();
					ImGuiFields::Space(5.0f);
					ImGui::Separator();
				}
			}

			//Transform Component
			if (entity.HasComponent<Transform>()) {
				if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
					Transform& trans = entity.GetComponent<Transform>();

					glm::vec3 position = trans.Position;
					glm::vec3 rotation = glm::degrees(trans.Rotation);
					glm::vec3 scale = trans.Scale;

					ImGuiFields::Vec3Field("TransformPosition", "Position ", position);
					ImGuiFields::Space(2);
					ImGuiFields::Vec3Field("TransformRotation", "Rotation ", rotation);
					ImGuiFields::Space(2);
					ImGuiFields::Vec3Field("TransformScale", "Scale ", scale, 1.0f);

					trans.Position = position;
					trans.Rotation = glm::radians(rotation);
					trans.Scale = scale;

					ImGui::TreePop();
					ImGuiFields::Space(5.0f);
					ImGui::Separator();
				}
			}

			//Camera Component
			if (entity.HasComponent<CameraComponent>()) {
				bool open = ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera");

				if (ImGuiFields::RightAlignedButton("+")) {
					ImGui::OpenPopup("ComponentSettings");
				}

				bool removeComponent = false;
				if (ImGui::BeginPopup("ComponentSettings")) {
					if (ImGui::MenuItem("Remove Component")) {
						removeComponent = true;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				if (open) {
					CameraComponent& cam = entity.GetComponent<CameraComponent>();
					SceneCamera& camera = cam.camera;

					ImGuiFields::Checkbox("CameraMainCameraCheck", "Main", &cam.main);
					ImGuiFields::Checkbox("CameraFixedAspectRatioCheck", "Fixed Aspect Ratio", &cam.fixedAspectRatio);

					std::vector<std::string> projectionTypeNames;
					projectionTypeNames.push_back("Orthographic");
					projectionTypeNames.push_back("Perspective");

					uint32_t currentlySelected = (uint32_t)camera.GetProjectionType();

					if (ImGuiFields::Dropdown("CameraProjectionType", "Projection", projectionTypeNames, currentlySelected)) {
						camera.SetProjectionType((SceneCamera::ProjectionType)currentlySelected);
					}

					if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orhtographic) {
						float orthoSize = camera.GetOrthoSize();
						if (ImGuiFields::FloatField("CameraOrthoSize", "Size", &orthoSize, 10.0f)) {
							camera.SetOrthoSize(orthoSize);
						}

						float orthoNear = camera.GetOrthoNear();
						if (ImGuiFields::FloatField("CameraOrthoNear", "Near", &orthoNear, -1.0f)) {
							camera.SetOrthoNear(orthoNear);
						}

						float orthoFar = camera.GetOrthoFar();
						if (ImGuiFields::FloatField("CameraOrhtoFar", "Far", &orthoFar, 1.0f)) {
							camera.SetOrthoFar(orthoFar);
						}
					}

					if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
						float fov = glm::degrees(camera.GetPerspectiveVerticalFOV());
						if (ImGuiFields::FloatField("CameraPerspectiveFOV", "Vertical FOV", &fov, 45.0f)) {
							camera.SetPerspectiveVerticalFOV(glm::radians(fov));
						}

						float nearClip = camera.GetPerspectiveNear();
						if (ImGuiFields::FloatField("CameraPerspectiveNear", "Near", &nearClip, 0.01f)) {
							camera.SetPerspectiveNear(nearClip);
						}

						float farClip = camera.GetPerspectiveFar();
						if (ImGuiFields::FloatField("CameraPerspectiveFar", "Far", &farClip, 1000.0f)) {
							camera.SetPerspectiveFar(farClip);
						}
					}

					ImGui::TreePop();
					ImGuiFields::Space(5.0f);
					ImGui::Separator();
				}

				if (removeComponent) entity.RemoveComponent<CameraComponent>();
			}

			//Sprite Renderer Component
			if (entity.HasComponent<SpriteRenderer>()) {
				bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer");
				if (ImGuiFields::RightAlignedButton("+")) {
					ImGui::OpenPopup("ComponentSettings");
				}

				bool removeComponent = false;
				if (ImGui::BeginPopup("ComponentSettings")) {
					if (ImGui::MenuItem("Remove Component")) {
						removeComponent = true;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				if (open) {
					SpriteRenderer& sprite = entity.GetComponent<SpriteRenderer>();
					ImGuiFields::Color4Field("SpriteRendererColor", "Color", sprite.m_color);
					ImGui::TreePop();
					ImGuiFields::Space(5.0f);
					ImGui::Separator();
				}

				if (removeComponent) entity.RemoveComponent<SpriteRenderer>();
			}
		}
	
	}
}