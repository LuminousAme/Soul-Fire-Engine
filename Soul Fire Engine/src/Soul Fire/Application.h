#pragma once

#include "EngineCore.h"

namespace SoulFire {
	class SF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined by client
	Application* CreateApplication();
}