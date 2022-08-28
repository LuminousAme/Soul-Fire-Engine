//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//VertexArrayObject.h - header file for the class that represnets a vertex array object that can interface with different API 
#pragma once

#include "SF_PCH.h"
#include "Buffer.h"

namespace SoulFire {
	class VertexArrayObject {
	public:
		typedef std::shared_ptr<VertexArrayObject> sptr;
	public:
		virtual ~VertexArrayObject() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const VertexBuffer::sptr& vbo) = 0;
		virtual void SetIndexBuffer(const IndexBuffer::sptr& ibo) = 0;

		virtual const std::vector<VertexBuffer::sptr>& GetVertexBuffers() const = 0;
		virtual const IndexBuffer::sptr& GetIndexBuffer() const = 0;

		virtual uint32_t GetVertexCount() const = 0;

		static VertexArrayObject* Create();
	};
}