#pragma once

#ifdef SF_PLATFORM_WINDOWS
	#ifdef SF_BUILDING_DLL
		#define SF_API __declspec(dllexport)
	#else
		#define SF_API __declspec(dllimport)
	#endif
#else 
	#error Soul Fire is currently on supported on windows.
#endif