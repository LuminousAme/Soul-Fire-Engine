//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//ImGuiLayer.cpp - source file for the layer that interfaces with ImGui

//precompile header
#include "SF_PCH.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "SoulFire/Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "SoulFire/Application.h"

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
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//temp use our own input system eventually
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_Apostrophe] = GLFW_KEY_APOSTROPHE;
		io.KeyMap[ImGuiKey_Comma] = GLFW_KEY_COMMA;
		io.KeyMap[ImGuiKey_Minus] = GLFW_KEY_MINUS;
		io.KeyMap[ImGuiKey_Period] = GLFW_KEY_PERIOD;
		io.KeyMap[ImGuiKey_Slash] = GLFW_KEY_SLASH;
		io.KeyMap[ImGuiKey_Semicolon] = GLFW_KEY_SEMICOLON;
		io.KeyMap[ImGuiKey_Equal] = GLFW_KEY_EQUAL;
		io.KeyMap[ImGuiKey_LeftBracket] = GLFW_KEY_LEFT_BRACKET;
		io.KeyMap[ImGuiKey_Backslash] = GLFW_KEY_BACKSLASH;
		io.KeyMap[ImGuiKey_RightBracket] = GLFW_KEY_RIGHT_BRACKET;
		io.KeyMap[ImGuiKey_GraveAccent] = GLFW_KEY_GRAVE_ACCENT;
		io.KeyMap[ImGuiKey_CapsLock] = GLFW_KEY_CAPS_LOCK;
		io.KeyMap[ImGuiKey_ScrollLock] = GLFW_KEY_SCROLL_LOCK;
		io.KeyMap[ImGuiKey_NumLock] = GLFW_KEY_NUM_LOCK;
		io.KeyMap[ImGuiKey_PrintScreen] = GLFW_KEY_PRINT_SCREEN;
		io.KeyMap[ImGuiKey_Pause] = GLFW_KEY_PAUSE;
		io.KeyMap[ImGuiKey_Keypad0] = GLFW_KEY_KP_0;
		io.KeyMap[ImGuiKey_Keypad1] = GLFW_KEY_KP_1;
		io.KeyMap[ImGuiKey_Keypad2] = GLFW_KEY_KP_2;
		io.KeyMap[ImGuiKey_Keypad3] = GLFW_KEY_KP_3;
		io.KeyMap[ImGuiKey_Keypad4] = GLFW_KEY_KP_4;
		io.KeyMap[ImGuiKey_Keypad5] = GLFW_KEY_KP_5;
		io.KeyMap[ImGuiKey_Keypad6] = GLFW_KEY_KP_6;
		io.KeyMap[ImGuiKey_Keypad7] = GLFW_KEY_KP_7;
		io.KeyMap[ImGuiKey_Keypad8] = GLFW_KEY_KP_8;
		io.KeyMap[ImGuiKey_Keypad9] = GLFW_KEY_KP_9;
		io.KeyMap[ImGuiKey_KeypadDecimal] = GLFW_KEY_KP_DECIMAL;
		io.KeyMap[ImGuiKey_KeypadDivide] = GLFW_KEY_KP_DIVIDE;
		io.KeyMap[ImGuiKey_KeypadMultiply] = GLFW_KEY_KP_MULTIPLY;
		io.KeyMap[ImGuiKey_KeypadSubtract] = GLFW_KEY_KP_SUBTRACT;
		io.KeyMap[ImGuiKey_KeypadAdd] = GLFW_KEY_KP_ADD;
		io.KeyMap[ImGuiKey_KeypadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_KeypadEqual] = GLFW_KEY_KP_EQUAL;
		io.KeyMap[ImGuiKey_LeftShift] = GLFW_KEY_LEFT_SHIFT;
		io.KeyMap[ImGuiKey_LeftCtrl] = GLFW_KEY_LEFT_CONTROL;
		io.KeyMap[ImGuiKey_LeftAlt] = GLFW_KEY_LEFT_ALT;
		io.KeyMap[ImGuiKey_LeftSuper] = GLFW_KEY_LEFT_SUPER;
		io.KeyMap[ImGuiKey_RightShift] = GLFW_KEY_RIGHT_SHIFT;
		io.KeyMap[ImGuiKey_RightCtrl] = GLFW_KEY_RIGHT_CONTROL;
		io.KeyMap[ImGuiKey_RightAlt] = GLFW_KEY_RIGHT_ALT;
		io.KeyMap[ImGuiKey_RightSuper] = GLFW_KEY_RIGHT_SUPER;
		io.KeyMap[ImGuiKey_Menu] = GLFW_KEY_MENU;
		io.KeyMap[ImGuiKey_0] = GLFW_KEY_0;
		io.KeyMap[ImGuiKey_1] = GLFW_KEY_1;
		io.KeyMap[ImGuiKey_2] = GLFW_KEY_2;
		io.KeyMap[ImGuiKey_3] = GLFW_KEY_3;
		io.KeyMap[ImGuiKey_4] = GLFW_KEY_4;
		io.KeyMap[ImGuiKey_5] = GLFW_KEY_5;
		io.KeyMap[ImGuiKey_6] = GLFW_KEY_6;
		io.KeyMap[ImGuiKey_7] = GLFW_KEY_7;
		io.KeyMap[ImGuiKey_8] = GLFW_KEY_8;
		io.KeyMap[ImGuiKey_9] = GLFW_KEY_9;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_B] = GLFW_KEY_B;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_D] = GLFW_KEY_D;
		io.KeyMap[ImGuiKey_E] = GLFW_KEY_E;
		io.KeyMap[ImGuiKey_F] = GLFW_KEY_F;
		io.KeyMap[ImGuiKey_G] = GLFW_KEY_G;
		io.KeyMap[ImGuiKey_H] = GLFW_KEY_H;
		io.KeyMap[ImGuiKey_I] = GLFW_KEY_I;
		io.KeyMap[ImGuiKey_J] = GLFW_KEY_J;
		io.KeyMap[ImGuiKey_K] = GLFW_KEY_K;
		io.KeyMap[ImGuiKey_L] = GLFW_KEY_L;
		io.KeyMap[ImGuiKey_M] = GLFW_KEY_M;
		io.KeyMap[ImGuiKey_N] = GLFW_KEY_N;
		io.KeyMap[ImGuiKey_O] = GLFW_KEY_O;
		io.KeyMap[ImGuiKey_P] = GLFW_KEY_P;
		io.KeyMap[ImGuiKey_Q] = GLFW_KEY_Q;
		io.KeyMap[ImGuiKey_R] = GLFW_KEY_R;
		io.KeyMap[ImGuiKey_S] = GLFW_KEY_S;
		io.KeyMap[ImGuiKey_T] = GLFW_KEY_T;
		io.KeyMap[ImGuiKey_U] = GLFW_KEY_U;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_W] = GLFW_KEY_W;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		io.KeyMap[ImGuiKey_F1] = GLFW_KEY_F1;
		io.KeyMap[ImGuiKey_F2] = GLFW_KEY_F2;
		io.KeyMap[ImGuiKey_F3] = GLFW_KEY_F3;
		io.KeyMap[ImGuiKey_F4] = GLFW_KEY_F4;
		io.KeyMap[ImGuiKey_F5] = GLFW_KEY_F5;
		io.KeyMap[ImGuiKey_F6] = GLFW_KEY_F6;
		io.KeyMap[ImGuiKey_F7] = GLFW_KEY_F7;
		io.KeyMap[ImGuiKey_F8] = GLFW_KEY_F8;
		io.KeyMap[ImGuiKey_F9] = GLFW_KEY_F9;
		io.KeyMap[ImGuiKey_F10] = GLFW_KEY_F10;
		io.KeyMap[ImGuiKey_F11] = GLFW_KEY_F11;
		io.KeyMap[ImGuiKey_F12] = GLFW_KEY_F12;

		io.SetClipboardTextFn = SetClipBoardText;
		io.GetClipboardTextFn = GetClipBoardText;
		io.ClipboardUserData = nullptr;

		ImGui_ImplOpenGL3_Init("#version 420");
	}

	void ImGuiLayer::Detach()
	{
	}

	void ImGuiLayer::Update()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& win = Application::GetApp().GetWindow();
		io.DisplaySize = ImVec2((float)win.GetWidth(), (float)win.GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);

		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTyped, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResize, this, std::placeholders::_1));
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL || io.KeysDown[GLFW_KEY_RIGHT_CONTROL]];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT || io.KeysDown[GLFW_KEY_RIGHT_SHIFT]];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT || io.KeysDown[GLFW_KEY_RIGHT_ALT]];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER || io.KeysDown[GLFW_KEY_RIGHT_SUPER]];

		return false;
	}



	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& ev) {
		ImGuiIO& io = ImGui::GetIO();

		int key = ev.GetKeyCode();

		if (key > 0 && key < 0x100000) io.AddInputCharacter((unsigned short)key);

		return false;
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(ev.GetX(), ev.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += ev.GetOffsetX();
		io.MouseWheel += ev.GetOffsetY();

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev.GetMouseButtonCode()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev.GetMouseButtonCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)ev.GetWidth(), (float)ev.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, ev.GetWidth(), ev.GetHeight());

		return false;
	}

	const char* ImGuiLayer::GetClipBoardText(void* data)
	{
		return Application::GetApp().GetWindow().GetClipBoardText();
	}

	void ImGuiLayer::SetClipBoardText(void* data, const char* text)
	{
		Application::GetApp().GetWindow().SetClipBoardText(text);
	}
}