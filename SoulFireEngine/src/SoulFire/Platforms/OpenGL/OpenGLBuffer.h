//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLBuffer.h - header file for the class that represnets vertex and index buffers for the OpenGL 3 API 
#pragma once

#include "SoulFire/Renderer/Buffer.h"
#include "glad/glad.h"

namespace SoulFire {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; };

		uint32_t GetCount() const override { return m_count; };
		uint32_t GetSize() const override { return m_size; };
	private:
		GLuint m_handle;
		BufferLayout m_layout;
		uint32_t m_count;
		uint32_t m_size;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		uint32_t GetCount() const override { return m_count; };
		IndexElementType GetElementType() const override { return m_elementType; };
	private:
		GLuint m_handle;
		uint32_t m_count;
		IndexElementType m_elementType;
	};
}