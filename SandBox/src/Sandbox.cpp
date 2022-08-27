#include <SoulFire.h>
#include "TestLayer.h"

class Sandbox : public SoulFire::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {}
};

SoulFire::Application* SoulFire::CreateApplication() {
	return new Sandbox();
}