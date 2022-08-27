//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//GraphicsContext.h - header file for a graphic context that can interface with different API
#pragma once

namespace SoulFire {
	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	};
}