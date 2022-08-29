//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//VertexArrayObject.h - header file for the class that represnets a vertex array object that can interface with different API 
#pragma once

#include "SF_PCH.h"
#include "Buffer.h"

namespace SoulFire {
	class VertexArrayObject {
	public:
		virtual ~VertexArrayObject() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const sptr<VertexBuffer>& vbo) = 0;
		virtual void SetIndexBuffer(const sptr<IndexBuffer>& ibo) = 0;

		virtual const std::vector<sptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const sptr<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual uint32_t GetVertexCount() const = 0;

		static sptr<VertexArrayObject> Create();
	};
}