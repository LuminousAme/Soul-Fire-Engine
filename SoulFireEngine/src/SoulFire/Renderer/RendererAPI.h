//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//RendererAPI.h - header file for the class that makes calls to the various rendering APIs
#pragma once

#include "SF_PCH.h"
#include "VertexArrayObject.h"

namespace SoulFire {
	class RendererAPI {
	public:
		enum class API {
			NONE = 0, OPENGL
		};
	public:
		virtual void Init() = 0;

		virtual void Clear(const glm::vec4& color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)) = 0;
		
		virtual void Draw(const sptr<VertexArrayObject>& VAO) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}