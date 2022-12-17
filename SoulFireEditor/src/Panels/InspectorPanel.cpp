//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//InspectorPanel.cpp - source file for the class that represents the panel to view the components of an entity

#include "InspectorPanel.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "glm/gtc/type_ptr.hpp"

namespace SoulFire {
	void InspectorPanel::OnImGuiRender(SceneHierarchyPanel& hierarchyPanel)
	{
		ImGui::Begin("Inspector");
		DrawComponents(hierarchyPanel.m_selectionContext);
		ImGui::End();
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetVal = 0.0f, float columnWidth = 100.0f) {
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.0f, 0.0f});

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize))
			values.x = resetVal;
		ImGui::PopStyleColor(3);
		ImGui::SameLine();


		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
			values.y = resetVal;
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
			values.z = resetVal;
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
	}

	void InspectorPanel::DrawComponents(Entity entity)
	{
		if (entity) {
			//Info Component
			if (entity.HasComponent<InfoComponent>()) {
				if (ImGui::TreeNodeEx((void*)typeid(InfoComponent).hash_code(),ImGuiTreeNodeFlags_DefaultOpen, "Entity")) {

					std::string& name = entity.GetComponent<InfoComponent>().m_name;

					ImGui::Columns(2);
					ImGui::SetColumnWidth(0, 100.0f);
					ImGui::Text("Name");
					ImGui::NextColumn();

					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					strcpy_s(buffer, sizeof(buffer), name.c_str());
					if (ImGui::InputText("", buffer, sizeof(buffer))) {
						name = std::string(buffer);
					}
					ImGui::Columns(1);
					ImGui::TreePop();
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

					DrawVec3Control("Position ", position);
					DrawVec3Control("Rotation ", rotation);
					DrawVec3Control("Scale ", scale, 1.0f);

					trans.Position = position;
					trans.Rotation = glm::radians(rotation);
					trans.Scale = scale;

					ImGui::TreePop();
					ImGui::Separator();
				}
			}

			//Sprite Renderer Component
			if (entity.HasComponent<SpriteRenderer>()) {
				if (ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer")) {
					
					SpriteRenderer& sprite = entity.GetComponent<SpriteRenderer>();
					ImGui::Columns(2);
					ImGui::SetColumnWidth(0, 100.0f);
					ImGui::Text("Color");
					ImGui::NextColumn();
					ImGui::ColorEdit4("", glm::value_ptr(sprite.m_color));
					ImGui::Columns(1);
					ImGui::TreePop();
					ImGui::Separator();
				}
			}


		}
	
	}
}