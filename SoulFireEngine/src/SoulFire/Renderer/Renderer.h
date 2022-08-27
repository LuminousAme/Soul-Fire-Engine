//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer.h - header file for the class that represnets the renderer that can interface with different API 
#pragma once

namespace SoulFire {
	enum class RendererAPI {
		NONE = 0,
		OPENGL
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}