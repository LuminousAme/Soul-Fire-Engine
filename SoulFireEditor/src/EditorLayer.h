#pragma once
#include <SoulFire.h>
#include <Imgui/imgui.h>

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
		sptr<Shader> m_testShader = nullptr;
		sptr<VertexArrayObject> m_testVAO = nullptr;
		Transform m_testTrans;

		glm::vec4 m_testColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		OrthograhpicCameraController m_testCameraController;
		sptr<SoulFire::Texture2D> m_testTexture;

		TextureProps m_testTextureProps;

		float rot = 0;

		bool dockspaceopen = true;

		sptr<Framebuffer> m_framebuffer;
		glm::vec2 m_viewportSize = glm::vec2(1280.0f, 720.0f);
	};
}