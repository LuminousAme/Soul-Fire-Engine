#include "EditorLayer.h"

namespace SoulFire {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_testCameraController(SoulFire::Application::GetApp().GetWindow().GetAspectRatio()),
		m_testTrans(SoulFire::Transform())
	{
	}

	void EditorLayer::Attach()
	{
		m_testTexture = SoulFire::Texture2D::Create("assets/textures/necoarctransparent.png");
		bool active = true;

		SoulFire::FramebufferSpecification spec;
		spec.Width = SoulFire::Application::GetApp().GetWindow().GetWidth();
		spec.Height = SoulFire::Application::GetApp().GetWindow().GetWidth();
		m_framebuffer = SoulFire::Framebuffer::Create(spec);
	}

	void EditorLayer::Detach()
	{
	}

	void EditorLayer::Update()
	{
		//Update
		m_testCameraController.Update();
		rot += (SoulFire::Time::GetDeltaTime() * 90.0f);
		while (rot > 360.0f) rot -= 360.0f;

		m_testTextureProps.tilingFactor = 5.0f;
		m_testTextureProps.tint = m_testColor;

		//Render
		m_framebuffer->Bind();
		m_framebuffer->SetViewport();
		int clearFlags = (SoulFire::ClearFlags::ClearColorBuffer | SoulFire::ClearFlags::ClearDepthBuffer);
		SoulFire::RenderCommand::Clear(clearFlags, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

		SoulFire::Renderer2D::BeginRenderPass(m_testCameraController.GetCamera());

		SoulFire::Renderer2D::DrawRotatedQuad(glm::vec2(-1.0f, 0.0f), glm::vec2(0.8f), rot, m_testTexture);
		SoulFire::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.75f), m_testColor);
		SoulFire::Renderer2D::DrawQuad(glm::vec2(-1.0f, -2.0f), glm::vec2(0.8f), m_testTexture);

		for (float y = -5.0f; y < 5.0f; y += 0.05f) {
			for (float x = -5.0f; x < 5.0f; x += 0.05f) {
				glm::vec4 color = glm::vec4((x + 5.0f) / 10.0f, 0.0f, (y + 5.0f) / 10.0f, 0.7f);
				SoulFire::Renderer2D::DrawQuad(glm::vec2(x, y), glm::vec2(0.045f, 0.045f), color);
			}
		}

		SoulFire::Renderer2D::EndRenderPass();
		m_framebuffer->UnBind();
	}

	void EditorLayer::OnEvent(SoulFire::Event& ev)
	{
		m_testCameraController.OnEvent(ev);
	}

	void EditorLayer::ImGuiRender()
	{
		DockSpace(&dockspaceopen);


	}

	//from: https://gist.github.com/moebiussurfing/8dbc7fef5964adcd29428943b78e45d2
	void EditorLayer::DockSpace(bool* p_open, bool fullscreen, bool padding)
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		if (fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();

			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

			// Manipulate the window flags to make it inaccessible to the user (no titlebar, resize/move, or navigation)
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", p_open, window_flags);

		if (!padding)
			ImGui::PopStyleVar();

		if (fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) SoulFire::Application::GetApp().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Sandbox2D Test Layer Box");
		std::stringstream fps;
		fps << "fps: " << 1.0f / SoulFire::Time::GetDeltaTime();
		ImGui::Text(fps.str().c_str());
		ImGui::ColorEdit4("Test Colour", glm::value_ptr(m_testColor));
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 currentViewportSize = { viewportPanelSize.x, m_viewportSize.y };
		if (currentViewportSize != m_viewportSize) {
			m_viewportSize = currentViewportSize;
			m_framebuffer->Resize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
			m_testCameraController.Resize(m_viewportSize.x, m_viewportSize.y);
		}

		uint32_t textID = m_framebuffer->GetColorAttachmentHandle(0);
		ImGui::Image((void*)textID, ImVec2(m_viewportSize.x, m_viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

}