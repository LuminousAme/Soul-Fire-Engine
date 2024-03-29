#include "EditorLayer.h"

namespace SoulFire {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
	}

	void EditorLayer::Attach()
	{
		m_activeScene = Scene::Create();

		m_testTexture = SoulFire::Texture2D::Create("assets/textures/necoarctransparent.png");
		bool active = true;

		SoulFire::FramebufferSpecification spec;
		spec.Width = SoulFire::Application::GetApp().GetWindow().GetWidth();
		spec.Height = SoulFire::Application::GetApp().GetWindow().GetWidth();
		m_framebuffer = SoulFire::Framebuffer::Create(spec);

		SoulFire::Application::GetApp().GetImGuiLayer()->SetDarkThemeColors();

		m_NecoArcEntity = m_activeScene->CreateEntity("Neco Arc");
		m_NecoArcEntity.AddComponent<SpriteRenderer>(m_testTexture);

		m_CameraEntity = m_activeScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_hierarchyPanel.SetContext(m_activeScene);

		SceneSerializer serializer(m_activeScene);
		serializer.Serialize("assets/scenes/Example.SF");
	}

	void EditorLayer::Detach()
	{
	}

	void EditorLayer::Update()
	{
		//Update
		//if(m_viewportFocused) m_testCameraController.Update();
		rot += (SoulFire::Time::GetDeltaTime() * 90.0f);
		while (rot > 360.0f) rot -= 360.0f;

		m_testTextureProps.tilingFactor = 5.0f;
		m_testTextureProps.tint = m_testColor;

		//Render
		m_framebuffer->Bind();
		m_framebuffer->SetViewport();
		int clearFlags = (SoulFire::ClearFlags::ClearColorBuffer | SoulFire::ClearFlags::ClearDepthBuffer);
		SoulFire::RenderCommand::Clear(clearFlags, glm::vec4(0.3f, 0.3f, 0.5f, 1.0f));

		//SoulFire::Renderer2D::BeginRenderPass(m_testCameraController.GetCamera());

		m_activeScene->Update();

		//SoulFire::Renderer2D::DrawRotatedQuad(glm::vec2(-1.0f, 0.0f), glm::vec2(0.8f), rot, m_testTexture);

		//SoulFire::Renderer2D::EndRenderPass();
		m_framebuffer->UnBind();
	}

	void EditorLayer::OnEvent(SoulFire::Event& ev)
	{
		//m_testCameraController.OnEvent(ev);
	}

	void EditorLayer::ImGuiRender()
	{
		DockSpace(&m_dockspaceopen);


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

		m_hierarchyPanel.OnImguiRender();
		m_inspectorPanel.OnImGuiRender(m_hierarchyPanel);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		m_viewportFocused = ImGui::IsWindowFocused();
		m_viewportHovered = ImGui::IsWindowHovered();
		Application::GetApp().GetImGuiLayer()->BlockEvents(!m_viewportFocused || !m_viewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 currentViewportSize = { viewportPanelSize.x, m_viewportSize.y };
		if (currentViewportSize != m_viewportSize && currentViewportSize.x > 0 && currentViewportSize.y > 0) {
			m_viewportSize = currentViewportSize;
			m_framebuffer->Resize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
			//m_testCameraController.Resize(m_viewportSize.x, m_viewportSize.y);
			m_activeScene->OnViewportResize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
		}

		uint32_t textID = m_framebuffer->GetColorAttachmentHandle(0);
		ImGui::Image((void*)textID, ImVec2(m_viewportSize.x, m_viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

}