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
private:
	//TEMP
	SoulFire::sptr<SoulFire::Shader> m_testShader = nullptr;
	SoulFire::sptr<SoulFire::VertexArrayObject> m_testVAO = nullptr;
	SoulFire::Transform m_testTrans;

	glm::vec4 m_testColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);

	SoulFire::OrthograhpicCameraController m_testCameraController;
	SoulFire::sptr<SoulFire::Texture2D> m_testTexture;

	float rot = 0;
};