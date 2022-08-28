//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer.h - header file for the class that represnets the renderer that can interface with different API 
#pragma once

#include "RenderCommand.h"

namespace SoulFire {

	class Renderer {
	public:
		static void BeginRenderPass();
		static void EndRenderPass();

		static void AddToPass(const VertexArrayObject::sptr& VAO);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}