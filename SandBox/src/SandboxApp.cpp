#include <SoulFire.h>
#include "TestLayer.h"
#include "Sandbox2D.h"
#include <SoulFire/Core/EntryPoint.h>

class Sandbox : public SoulFire::Application {
public:
	Sandbox() {
		//PushLayer(new TestLayer());
		PushLayer(new Sandbox2DLayer());
	}

	~Sandbox() {}
};

SoulFire::Application* SoulFire::CreateApplication() {
	return new Sandbox();
}