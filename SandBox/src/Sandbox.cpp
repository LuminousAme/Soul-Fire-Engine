#include <SoulFire.h>

class Sandbox : public SoulFire::Application {
public:
	Sandbox() {
		SF_LOG_INFO("Test but from the acutal application this time >:3");
	}

	~Sandbox() {}
};

SoulFire::Application* SoulFire::CreateApplication() {
	return new Sandbox();
}