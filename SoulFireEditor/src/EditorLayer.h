#pragma once
#include <SoulFire.h>
#include <Imgui/imgui.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/InspectorPanel.h"

namespace SoulFire {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void Attach() override;
		void Detach() override;

		void Update() override;
		void OnEvent(SoulFire::Event& ev) override;
		void ImGuiRender() override;

		void DockSpace(bool* p_open, bool fullscreen = true, bool padding = false);
	private:
		//TEMP
		glm::vec4 m_testColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		sptr<SoulFire::Texture2D> m_testTexture;

		TextureProps m_testTextureProps;

		float rot = 0;

	private: 
		sptr<Scene> m_activeScene;
		Entity m_NecoArcEntity;
		Entity m_CameraEntity;
	private:
		bool m_dockspaceopen = true;
		bool m_viewportFocused = false;
		bool m_viewportHovered = false;
		sptr<Framebuffer> m_framebuffer;
		glm::vec2 m_viewportSize = glm::vec2(1280.0f, 720.0f);

		SceneHierarchyPanel m_hierarchyPanel;
		InspectorPanel m_inspectorPanel;
	};
}