//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLRendererAPI.h - header file for the class that makes handles the rendering for the OpenGL API
#pragma once

#include "SoulFire/Renderer/RendererAPI.h"
namespace SoulFire {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();

		void Clear(const glm::vec4& color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

		void Draw(const VertexArrayObject::sptr& VAO) override;
	private:
		glm::vec4 m_clearColor;
	};
}