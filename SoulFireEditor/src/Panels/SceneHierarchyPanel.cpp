//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneHierarchyPanel.cpp - source file for the class that represents the scenegraph

#include "SceneHierarchyPanel.h"
#include "Imgui/imgui.h"
#include "SoulFire/ImGui/ImGuiFields.h"

namespace SoulFire {
	SceneHierarchyPanel::SceneHierarchyPanel(const sptr<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyPanel::SetContext(const sptr<Scene>& scene)
	{
		m_context = scene;
	}

	void SceneHierarchyPanel::OnImguiRender()
	{
		ImGui::Begin("Hierarchy");

		m_context->m_registry.each([&](auto entityID) {
			Entity entity = Entity(entityID, m_context.get());
			DrawEntityNode(entity);
		});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_selectionContext = Entity();

		//right clicking on a blank space
		if (ImGui::BeginPopupContextWindow(0, 1, false)) {
			ImGuiFields::Text("Create Entity");
			ImGuiFields::Seperator();
			if(ImGui::MenuItem("Empty")) m_context->CreateEntity();

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		std::string& name = entity.GetComponent<InfoComponent>().m_name;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= (entity == m_selectionContext) ? ImGuiTreeNodeFlags_Selected : 0;
		bool expanded = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, name.c_str());

		if (ImGui::IsItemClicked()) {
			m_selectionContext = entity;
		}

		bool deleteEntity = false;
		if (ImGui::BeginPopupContextItem()) {
			if (ImGui::MenuItem("Delete Entity")) deleteEntity = true;

			ImGui::EndPopup();
		}

		if (expanded) {
			//child nodes here
			ImGui::TreePop();
		}

		if (deleteEntity) {
			if (m_selectionContext == entity) m_selectionContext = Entity();
			m_context->Destroy(entity);
		}
	}
}


