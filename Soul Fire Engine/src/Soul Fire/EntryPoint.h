#pragma once
#include "Application.h"

#ifdef SF_PLATFORM_WINDOWS

extern SoulFire::Application* SoulFire::CreateApplication();

int main(int argc, char** argv) {
	//create the application
	auto app = SoulFire::CreateApplication();
	
	//run it
	app->Run();

	//when it finishes running delete it
	delete app;

	//and exit with no error
	return 0;
}

#endif