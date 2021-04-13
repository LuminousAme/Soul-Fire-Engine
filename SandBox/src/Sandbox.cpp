#include <SoulFire.h>

class Sandbox : public SoulFire::Application {
public:
	Sandbox() {}

	~Sandbox() {}
};

SoulFire::Application* SoulFire::CreateApplication() {
	return new Sandbox();
}