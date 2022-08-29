//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//WindowsTime.cpp - source file for the class that manages time and timesteps on the windows platform

#include "SF_PCH.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"
#include "WindowsTime.h"

namespace SoulFire {

	void WindowsTime::StartFrame()
	{
		m_time = (float)glfwGetTime();
		m_deltaTime = m_time - m_lastFrameTime;
	}

	void WindowsTime::EndFrame()
	{
		m_lastFrameTime = m_time;
	}
}