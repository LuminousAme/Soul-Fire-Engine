//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLBuffer.cpp - source file for the class that represnets vertex and index buffers for the OpenGL 3 API 
#include "SF_PCH.h"
#include "OpenGLBuffer.h"

namespace SoulFire {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		: m_count(sizeof(vertices) / sizeof(float)), m_size(size)
	{
		glCreateBuffers(1, &m_handle);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		UnBind();
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
		: m_count(0), m_size(size)
	{
		glCreateBuffers(1, &m_handle);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		UnBind();
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_handle);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_handle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_count(count), m_elementType(IndexElementType::UNSIGNEDINT)
	{
		glCreateBuffers(1, &m_handle);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		UnBind();
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_handle);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}