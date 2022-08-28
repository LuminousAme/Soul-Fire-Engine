//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Rendercommand.cpp - source file for the class that allows the engine and client to make calls to the renderer

#include "SF_PCH.h"
#include "RenderCommand.h"

#include "SoulFire/Platforms/OpenGL/OpenGLRendererAPI.h"

namespace SoulFire {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}