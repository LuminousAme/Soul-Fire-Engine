//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//ImGuiLayer.cpp - source file for the layer that interfaces with ImGui

//precompile header
#include "SF_PCH.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "SoulFire/Core/Application.h"

//temp, replace when doing acutal rendering later
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace SoulFire {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::Attach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); 
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindowPointer());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 420");
	}

	void ImGuiLayer::Detach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::ImGuiRender()
	{
	}

	void ImGuiLayer::OnEvent(Event& ev)
	{
		if (m_BlockEvents) {
			ImGuiIO& io = ImGui::GetIO();
			if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
				EventDispatcher dispatcher(ev);

				dispatcher.Dispatch<KeyPressedEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));
				dispatcher.Dispatch<KeyReleasedEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));
				dispatcher.Dispatch<KeyTypedEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));

				dispatcher.Dispatch<MouseMovedEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));
				dispatcher.Dispatch<MouseScrolledEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));
				dispatcher.Dispatch<MouseButtonPressedEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));
				dispatcher.Dispatch<MouseButtonReleasedEvent>(SF_BIND_EVENT_FN(ImGuiLayer::BlockEventFunc));
			}
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		auto[width, height] = Application::GetApp().GetWindow().GetWindowSize();

		io.DisplaySize = ImVec2((float)width, (float)height);

		//render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//viewports
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(current_context);
		}
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		ImGui::StyleColorsDark();
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.05f, 0.0505f, 0.051f, 1.0f };

		//Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.075f, 0.07505f, 0.0751f, 1.0f };

		//Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		//Frame backgrounds
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		//Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.075f, 0.07505f, 0.075f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.18f, 0.1805f, 0.181f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.14f, 0.1405f, 0.141f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.075f, 0.07505f, 0.0751f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		//Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.075f, 0.07505f, 0.0751f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.075f, 0.07505f, 0.0751f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.075f, 0.07505f, 0.0751f, 1.0f };

		//misc
		colors[ImGuiCol_CheckMark] = ImVec4{0.8f, 0.8f, 0.8f, 1.0f};
		colors[ImGuiCol_Text] = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
	}

	void ImGuiLayer::SetLightThemeColors()
	{
		ImGui::StyleColorsLight();
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		//Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.675f, 0.67505f, 0.6751f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		//Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.7f, 0.705f, 0.71f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		//Frame backgrounds
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.7f, 0.705f, 0.71f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.75f, 0.7505f, 0.751f, 1.0f };

		//Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.68f, 0.6805f, 0.681f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.64f, 0.6405f, 0.641f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.775f, 0.77505f, 0.7751f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };

		//Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.775f, 0.77505f, 0.7751f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.775f, 0.77505f, 0.7751f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.775f, 0.77505f, 0.7751f, 1.0f };

		//misc
		colors[ImGuiCol_CheckMark] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
		colors[ImGuiCol_Text] = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
	}

	bool ImGuiLayer::BlockEventFunc(Event& ev)
	{
		//mark the event as handled
		return true;
	}
}