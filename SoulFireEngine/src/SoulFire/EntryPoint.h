//Soul Fire Engine By Ame Gilham 
//Application.h - header file for that acts as the entry point for Soul Fire applications
#pragma once
#include "Application.h"
#include "Logger.h"

//if the platform is windows
#ifdef SF_PLATFORM_WINDOWS

extern SoulFire::Application* SoulFire::CreateApplication();

int main(int argc, char** argv) {
	//start up the logger system
	SoulFire::Logger::Init();

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