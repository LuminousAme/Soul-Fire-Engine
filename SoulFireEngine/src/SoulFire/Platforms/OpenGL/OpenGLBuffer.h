//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLBuffer.h - header file for the class that represnets vertex and index buffers for the OpenGL 3 API 
#pragma once

#include "SoulFire/Renderer/Buffer.h"
#include "glad/glad.h"

namespace SoulFire {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;
	private:
		GLuint m_handle;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		uint32_t GetCount() const override { return m_count; };
	private:
		GLuint m_handle;
		uint32_t m_count;
	};
}