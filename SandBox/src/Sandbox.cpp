#include <SoulFire.h>

class Sandbox : public SoulFire::Application {
public:
	Sandbox() {
		PushOverlay(new SoulFire::ImGuiLayer());
	}

	~Sandbox() {}
};

SoulFire::Application* SoulFire::CreateApplication() {
	return new Sandbox();
}