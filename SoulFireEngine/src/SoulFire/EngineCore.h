//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Engine.h - header file that defines the marcos for dll use and to support accross different platforms
#pragma once

#include "SF_PCH.h"

#ifdef SF_PLATFORM_WINDOWS
	#ifdef SF_BUILDING_DLL
		#define SF_API __declspec(dllexport)
	#else
		#define SF_API __declspec(dllimport)
	#endif
#else 
	#error Soul Fire is currently on supported on windows only.
#endif

//tell GLFW to not import OpenGL cause Glad imports it too.
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif