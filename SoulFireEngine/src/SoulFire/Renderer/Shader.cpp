//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Shader.cpp - source file for the class that represnets a complete shader program that can interface with different API 
#include "SF_PCH.h"
#include "Shader.h"

#include "SoulFire/Platforms/OpenGL/OpenGLShader.h"

namespace SoulFire {
	Shader* Shader::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::OPENGL:
			return new OpenGLShader();
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");

		return nullptr;
	}
}