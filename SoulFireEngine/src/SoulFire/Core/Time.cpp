//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Time.cpp - source file for the class that manages time and timesteps

#include "SF_PCH.h"
#include "Time.h"

#include "SoulFire/Platforms/Windows/WindowsTime.h"

namespace SoulFire {
	std::unique_ptr<Time> Time::time = nullptr;

	float Time::GetTime()
	{
		if (time == nullptr) Create();

		return time->m_time;
	}

	float Time::GetLastFrameTime()
	{
		if (time == nullptr) Create();

		return time->m_lastFrameTime;
	}

	float Time::GetDeltaTime()
	{
		if (time == nullptr) Create();

		return time->m_deltaTime;
	}

	float Time::GetDeltaTimeMilliseconds()
	{
		return GetDeltaTime() * 1000.0f;
	}

	void Time::BeginFrame()
	{
		if (time == nullptr) Create();

		time->StartFrame();
	}

	void Time::StopFrame()
	{
		if (time == nullptr) Create();

		time->EndFrame();
	}

	Time* Time::Create(float time)
	{
		Time* timePtr = new WindowsTime(time);
		Time::time.reset(timePtr);
		return timePtr;
	}
}

