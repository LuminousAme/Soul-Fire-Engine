//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//WindowsTime.h - header file for the class that manages time and timesteps on the windows platform
#pragma once

#include "SoulFire/Core/Time.h"
#include "GLFW/glfw3.h"

namespace SoulFire {
	class WindowsTime : public Time {
	public:
		WindowsTime(float time) 
		: Time(time)
		{}
		void StartFrame() override;
		void EndFrame() override;
	};
}