//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneHierarchyPanel.cpp - source file for the class that represents the scenegraph

#include "SceneHierarchyPanel.h"
#include "Imgui/imgui.h"

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

		if (expanded) {
			ImGui::TreePop();
		}
	}
}


