//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLRendererAPI.cpp - source file for the class that makes handles the rendering for the OpenGL API

#include "SF_PCH.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace SoulFire {
	static GLenum IndexElementTypeToOpenGLNativeType(IndexElementType type) {
		switch (type) {
		case IndexElementType::UNSIGNEDINT:		return GL_UNSIGNED_INT;
		}

		SF_ENGINE_LOG_ASSERT(false, "Unknown IndexElementType");
		return GL_NONE;
	}

	OpenGLRendererAPI::OpenGLRendererAPI()
		: m_clearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f))
	{
	}

	void OpenGLRendererAPI::Clear(const glm::vec4& color)
	{
		if (color != m_clearColor) {
			m_clearColor = color;
			glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		}

		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::Draw(const VertexArrayObject::sptr& VAO)
	{
		VAO->Bind();
		if (VAO->GetIndexBuffer() != nullptr) {
			glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), IndexElementTypeToOpenGLNativeType(VAO->GetIndexBuffer()->GetElementType()), nullptr);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, VAO->GetVertexCount());
		}
		VAO->UnBind();
	}
}