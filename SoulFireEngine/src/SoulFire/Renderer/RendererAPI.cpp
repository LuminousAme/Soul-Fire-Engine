//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//RendererAPI.cpp - source file for the class that makes calls to the various rendering APIs
#include "SF_PCH.h"
#include "RendererAPI.h"

namespace SoulFire {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPENGL;
}