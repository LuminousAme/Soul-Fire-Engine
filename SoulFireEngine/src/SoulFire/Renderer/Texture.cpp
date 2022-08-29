//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Texture.cpp - source file for the classes that represent textures regardless of API

#include "SF_PCH.h"
#include "Texture.h"

#include "SoulFire/Platforms/OpenGL/OpenGLTexture.h"


namespace SoulFire {
	sptr<Texture2D> Texture2D::Create(const std::string& filepath, bool generateMipmaps)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::API::OPENGL:
			return std::make_shared<OpenGLTexture2D>(filepath, generateMipmaps);
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");

		return nullptr;
	}
}