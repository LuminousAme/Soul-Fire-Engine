//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Framebuffer.cpp - source file for the classes that represent framebuffers regardless of API

#include "SF_PCH.h"
#include "Framebuffer.h"
#include "SoulFire/Platforms/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"

namespace SoulFire {
	sptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec, bool withDepth, uint32_t colorBuffers, uint32_t format)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::API::OPENGL:
			return std::make_shared<OpenGLFramebuffer>(spec, withDepth, colorBuffers, format);
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");
		return nullptr;
	}
}