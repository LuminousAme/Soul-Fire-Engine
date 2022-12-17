#include <SoulFire.h>
#include <SoulFire/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace SoulFire {
	class Editor : public Application {
	public:
		Editor() {
			//PushLayer(new TestLayer());
			PushLayer(new EditorLayer());
		}

		~Editor() {}
	};

	SoulFire::Application* SoulFire::CreateApplication() {
		return new Editor();
	}
}
