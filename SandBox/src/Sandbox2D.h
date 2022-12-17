#pragma once
#include <SoulFire.h>
#include <Imgui/imgui.h>

class Sandbox2DLayer : public SoulFire::Layer {
public:
	Sandbox2DLayer();
	virtual ~Sandbox2DLayer() = default;

	void Attach() override;
	void Detach() override;

	void Update() override;
	void OnEvent(SoulFire::Event& ev) override;
	void ImGuiRender() override;

	void DockSpace(bool* p_open, bool fullscreen = true, bool padding = false);
private:
	//TEMP
	SoulFire::sptr<SoulFire::Shader> m_testShader = nullptr;
	SoulFire::sptr<SoulFire::VertexArrayObject> m_testVAO = nullptr;
	SoulFire::Transform m_testTrans;

	glm::vec4 m_testColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	SoulFire::OrthograhpicCameraController m_testCameraController;
	SoulFire::sptr<SoulFire::Texture2D> m_testTexture;

	SoulFire::TextureProps m_testTextureProps;

	float rot = 0;

	bool dockspaceopen = true;

	SoulFire::sptr<SoulFire::Framebuffer> m_framebuffer;
	glm::vec2 m_viewportSize = glm::vec2(1280.0f, 720.0f);
};