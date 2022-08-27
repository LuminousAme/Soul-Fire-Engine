//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//GraphicsContext.cpp - source file for a graphic context in the OpenGL 3 API

#include "SF_PCH.h"
#include "OpenGLContext.h"
#include "glad/glad.h"

namespace SoulFire {
	OpenGLContext::OpenGLContext(GLFWwindow* window) :
		m_window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_window);

		//initliaze glad
		int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SF_ENGINE_LOG_ASSERT(gladLoadStatus, "Glad initalization failed!");

		SF_ENGINE_LOG_INFO("Rendering Information for OpenGL: ")
		SF_ENGINE_LOG_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		SF_ENGINE_LOG_INFO("	Card: {0}", glGetString(GL_RENDERER));
		SF_ENGINE_LOG_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void SoulFire::OpenGLContext::SwapBuffers()
	{
		//swap the front and backbuffers
		glfwSwapBuffers(m_window);
	}
}


