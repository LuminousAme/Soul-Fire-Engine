//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLVertexArrayObject.h - header file for the class that represnets a vertex array object in the OpenGL API
#pragma once

#include "SoulFire/Renderer/VertexArrayObject.h"
#include "glad/glad.h"

namespace SoulFire {
	class OpenGLVertexArrayObject : public VertexArrayObject {
	public:
		OpenGLVertexArrayObject();
		virtual ~OpenGLVertexArrayObject();

		void Bind() const override;
		void UnBind() const override;

		void AddVertexBuffer(const VertexBuffer::sptr& vbo) override;
		void SetIndexBuffer(const IndexBuffer::sptr& ibo) override;

		const std::vector<VertexBuffer::sptr>& GetVertexBuffers() const override { return m_VBOs; };
		const IndexBuffer::sptr& GetIndexBuffer() const override { return m_IBO; };

		uint32_t GetVertexCount() const override { return m_vertexCount; };

	private:
		std::vector<VertexBuffer::sptr> m_VBOs;
		IndexBuffer::sptr m_IBO;
		GLuint m_handle;
		uint32_t m_vertexCount;
	};
}