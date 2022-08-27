#include <SoulFire.h>
#include "TestLayer.h"

class Sandbox : public SoulFire::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
		PushOverlay(new SoulFire::ImGuiLayer());
	}

	~Sandbox() {}
};

SoulFire::Application* SoulFire::CreateApplication() {
	return new Sandbox();
}