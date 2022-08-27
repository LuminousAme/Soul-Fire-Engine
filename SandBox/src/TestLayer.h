#pragma once
#include <SoulFire.h>

class TestLayer : public SoulFire::Layer {
public:
	TestLayer()
		: Layer("App Test")
	{
		lastPos = glm::vec2(SoulFire::Input::GetMouseX(), SoulFire::Input::GetMouseY());
	}

	void Update() {
		if (SoulFire::Input::GetKeyDown(SF_KEY_TAB)) {
			glm::vec2 currentPos = glm::vec2(SoulFire::Input::GetMouseX(), SoulFire::Input::GetMouseY());

			float dist = glm::distance(currentPos, lastPos);
			SF_LOG_TRACE("Current position: {0}, {1}! Last Position: {2}, {3}!", currentPos.x, currentPos.y, lastPos.x, lastPos.y);
			SF_LOG_TRACE("The mouse has moved {0} pixels!", dist);

			lastPos = currentPos;
		}
	}
private:
	glm::vec2 lastPos = glm::vec2(0.0f, 0.0f);
};