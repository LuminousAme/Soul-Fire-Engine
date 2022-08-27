//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Buffer.h - header file for the class that represnets vertex and index buffers that can interface with different API 
#pragma once

#include <stdint.h>

namespace SoulFire {
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const  = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}