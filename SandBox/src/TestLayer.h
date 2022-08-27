#pragma once
#include <SoulFire.h>

class TestLayer : public SoulFire::Layer {
public:
	TestLayer()
		: Layer("App Test")
	{
	}

	void Update() {
		if (SoulFire::Input::GetKeyDown(SF_KEY_TAB)) {
			SF_LOG_TRACE("Hello!");
		}
	}
};