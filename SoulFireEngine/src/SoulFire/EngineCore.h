//Soul Fire Engine By Ame Gilham 
//Engine.h - header file that defines the marcos for dll use and to support accross different platforms
#pragma once

#ifdef SF_PLATFORM_WINDOWS
	#ifdef SF_BUILDING_DLL
		#define SF_API __declspec(dllexport)
	#else
		#define SF_API __declspec(dllimport)
	#endif
#else 
	#error Soul Fire is currently on supported on windows only.
#endif