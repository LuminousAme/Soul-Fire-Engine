//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Buffer.h - header file for the class that represnets vertex and index buffers that can interface with different API 
#include "SF_PCH.h"
#include "Buffer.h"
#include "Renderer.h"

#include "SoulFire/Platforms/OpenGL/OpenGLBuffer.h"

namespace SoulFire {

	sptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::API::OPENGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");
		return nullptr;
	}

	sptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::API::OPENGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");
		return nullptr;
	}
}