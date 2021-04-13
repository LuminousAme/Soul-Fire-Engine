//Soul Fire Engine By Ame Gilham 
//Application.h - header file for the class that represnets a Soul Fire Application
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