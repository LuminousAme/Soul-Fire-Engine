//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer.cpp - source file for the class that represnets the renderer that can interface with different API 
#include "SF_PCH.h"
#include "Renderer.h"

namespace SoulFire {
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OPENGL;
}