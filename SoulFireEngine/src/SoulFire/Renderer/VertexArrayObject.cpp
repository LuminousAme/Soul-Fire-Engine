//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//VertexArrayObject.cpp - source file for the class that represnets a vertex array object that can interface with different API 

#include "SF_PCH.h"
#include "VertexArrayObject.h"
#include "Renderer.h"

#include "SoulFire/Platforms/OpenGL/OpenGLVertexArrayObject.h"

namespace SoulFire {

	VertexArrayObject* VertexArrayObject::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::API::OPENGL:
			return new OpenGLVertexArrayObject();
			break;
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");
		return nullptr;
	}
}