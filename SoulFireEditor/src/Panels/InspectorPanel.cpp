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
		Entity entity = hierarchyPanel.m_selectionContext;
		if (entity != Entity()) {
			DrawComponents(entity);
			ImGuiFields::Space(5.0f);
			if (ImGuiFields::CentreAlignedButton("Add Component", { 100.0f, 20.0f })) ImGui::OpenPopup("AddComponent");
			if (ImGui::BeginPopup("AddComponent")) {
				if (!entity.HasComponent<CameraComponent>()) {
					if (ImGui::MenuItem("Camera")) {
						entity.AddComponent<CameraComponent>();
						ImGui::CloseCurrentPopup();
					}
				}

				if (!entity.HasComponent<SpriteRenderer>()) {
					if (ImGui::MenuItem("SpriteRenderer")) {
						entity.AddComponent<SpriteRenderer>();
						ImGui::CloseCurrentPopup();
					}
				}

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}

	template<typename T, typename UIFunction>
	static void DrawComponentNonRemoveable(const std::string& label, Entity entity, UIFunction uifunction) {
		if (entity.HasComponent<T>()) {
			T& component = entity.GetComponent<T>();

			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, label.c_str());

			if (open) {
				uifunction(component);
				ImGui::TreePop();
				ImGuiFields::Space(5.0f);
				ImGui::Separator();
			}
		}
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& label, Entity entity, UIFunction uifunction) {
		if (entity.HasComponent<T>()) {
			T& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvaiable = ImGui::GetContentRegionAvail();


			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAvailWidth;
			treeNodeFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, label.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvaiable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight , lineHeight })) {
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
				uifunction(component);
				ImGui::TreePop();
				ImGuiFields::Space(5.0f);
				ImGui::Separator();
			}

			if (removeComponent) entity.RemoveComponent<T>();
		}
	}

	void InspectorPanel::DrawComponents(Entity entity)
	{
		if (entity) {
			//Info Component
			DrawComponentNonRemoveable<InfoComponent>("Entity", entity, [](auto& component) {
				std::string& name = component.m_name;
				ImGuiFields::ShortTextField("EntityName", "Name", name);
			});

			//Transform Component
			DrawComponentNonRemoveable<Transform>("Transform", entity, [](auto& component) {
				glm::vec3 position = component.Position;
				glm::vec3 rotation = glm::degrees(component.Rotation);
				glm::vec3 scale = component.Scale;

				ImGuiFields::Vec3Field("TransformPosition", "Position ", position);
				ImGuiFields::Space(2);
				ImGuiFields::Vec3Field("TransformRotation", "Rotation ", rotation);
				ImGuiFields::Space(2);
				ImGuiFields::Vec3Field("TransformScale", "Scale ", scale, 1.0f);

				component.Position = position;
				component.Rotation = glm::radians(rotation);
				component.Scale = scale;
			});

			//Camera Component
			DrawComponent<CameraComponent>("Camera", entity, [](auto& component) {
				SceneCamera& camera = component.camera;

				ImGuiFields::Checkbox("CameraMainCameraCheck", "Main", &component.main);
				ImGuiFields::Checkbox("CameraFixedAspectRatioCheck", "Fixed Aspect Ratio", &component.fixedAspectRatio);

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
			});

			//Sprite Renderer Component
			DrawComponent<SpriteRenderer>("Sprite Renderer", entity, [](auto& component) {
				ImGuiFields::Color4Field("SpriteRendererColor", "Color", component.m_color);
			});
		}
	
	}
}