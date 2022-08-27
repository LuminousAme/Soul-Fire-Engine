//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//GraphicsContext.h - header file for a graphic context in the OpenGL 3 API
#pragma once

#include "SoulFire/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace SoulFire {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_window;
	};
}