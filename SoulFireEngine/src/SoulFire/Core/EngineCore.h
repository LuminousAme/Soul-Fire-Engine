//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Engine.h - header file that defines the marcos for dll use and to support accross different platforms
#pragma once

#include "SF_PCH.h"

#ifdef SF_PLATFORM_WINDOWS
	#ifdef SF_DYNAMIC_LINK
		#ifdef SF_BUILDING_DLL
			#define SF_API __declspec(dllexport)
		#else
			#define SF_API __declspec(dllimport)
		#endif
	#else
		#define SF_API
	#endif
#else 
	#error Soul Fire is currently on supported on windows only.
#endif

//tell GLFW to not import OpenGL cause Glad imports it too.
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#define SF_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace SoulFire {
	template<typename T>
	using uptr = std::unique_ptr<T>;

	template<typename T>
	using sptr = std::shared_ptr<T>;
}