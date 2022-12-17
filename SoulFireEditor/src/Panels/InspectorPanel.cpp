//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//InspectorPanel.cpp - source file for the class that represents the panel to view the components of an entity

#include "InspectorPanel.h"
#include "Imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

namespace SoulFire {
	void InspectorPanel::OnImGuiRender(SceneHierarchyPanel& hierarchyPanel)
	{
		ImGui::Begin("Inspector");
		DrawComponents(hierarchyPanel.m_selectionContext);
		ImGui::End();
	}

	void InspectorPanel::DrawComponents(Entity entity)
	{
		if (entity) {
			//Info Component
			if (entity.HasComponent<InfoComponent>()) {
				if (ImGui::TreeNodeEx((void*)typeid(InfoComponent).hash_code(),ImGuiTreeNodeFlags_DefaultOpen, "Entity")) {
					std::string& name = entity.GetComponent<InfoComponent>().m_name;

					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					strcpy_s(buffer, sizeof(buffer), name.c_str());
					if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
						name = std::string(buffer);
					}

					ImGui::TreePop();
				}
			}

			//Transform Component
			if (entity.HasComponent<Transform>()) {
				if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
					glm::mat4& trans = entity.GetComponent<Transform>().m_transform;

					if (ImGui::DragFloat3("Position", glm::value_ptr(trans[3]), 0.1f)) {

					}

					ImGui::TreePop();
				}
			}

			//Sprite Renderer Component
			if (entity.HasComponent<SpriteRenderer>()) {
				if (ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer")) {
					
					SpriteRenderer& sprite = entity.GetComponent<SpriteRenderer>();
					ImGui::ColorEdit4("Color", glm::value_ptr(sprite.m_color));
					ImGui::TreePop();
				}
			}


		}
	
	}
}