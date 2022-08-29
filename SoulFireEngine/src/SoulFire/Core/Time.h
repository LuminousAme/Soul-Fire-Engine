//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Time.h - header file for the class that manages time and timesteps
#pragma once

namespace SoulFire {
	class Time {
	public:
		Time(float time)
			: m_time(time), m_lastFrameTime(0.0f), m_deltaTime(0.0f)
		{
		}

	public:
		static float GetTime();
		static float GetLastFrameTime();
		static float GetDeltaTime();
		static float GetDeltaTimeMilliseconds();
		static void BeginFrame();
		static void StopFrame();

	protected:
		static std::unique_ptr<Time> time;
		static Time* Create(float time = 0.0f);

		virtual void StartFrame() = 0;
		virtual void EndFrame() = 0;
	protected:
		float m_time;
		float m_lastFrameTime;
		float m_deltaTime;
	};
}