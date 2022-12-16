#include "Sandbox2D.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2D"), m_testCameraController(SoulFire::Application::GetApp().GetWindow().GetAspectRatio()), 
	m_testTrans(SoulFire::Transform())
{
}

void Sandbox2DLayer::Attach()
{
	m_testTexture = SoulFire::Texture2D::Create("assets/textures/necoarctransparent.png");
}

void Sandbox2DLayer::Detach()
{
}

void Sandbox2DLayer::Update()
{
	//Update
	m_testCameraController.Update();
	rot += (SoulFire::Time::GetDeltaTime() * 90.0f);
	while (rot > 360.0f) rot -= 360.0f;

	//Render
	int clearFlags = (SoulFire::ClearFlags::ClearColorBuffer | SoulFire::ClearFlags::ClearDepthBuffer);
	SoulFire::RenderCommand::Clear(clearFlags, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	SoulFire::Renderer2D::BeginRenderPass(m_testCameraController.GetCamera());

	SoulFire::Renderer2D::DrawRotatedQuad(glm::vec2(-1.0f, 0.0f), glm::vec2(0.8f), rot, m_testTexture);
	SoulFire::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f), m_testColor);

	SoulFire::Renderer2D::EndRenderPass();
}

void Sandbox2DLayer::OnEvent(SoulFire::Event& ev)
{
	m_testCameraController.OnEvent(ev);
}

void Sandbox2DLayer::ImGuiRender()
{
	ImGui::Begin("Sandbox2D Test Layer Box");
	ImGui::ColorEdit4("Test Colour", glm::value_ptr(m_testColor));
	ImGui::End();
}
