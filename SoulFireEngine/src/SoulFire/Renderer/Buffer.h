//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Buffer.h - header file for the class that represnets vertex and index buffers that can interface with different API 
#pragma once

#include <stdint.h>

namespace SoulFire {
	enum class ShaderDataType {
		None = 0, Float, Vec2, Vec3, Vec4, Mat3, Mat4, Int, IVec2, IVec3, IVec4, Bool
	};

	enum class IndexElementType {
		None = 0, UNSIGNEDINT
	};

	static uint32_t CalculateDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float :	return 4;
		case ShaderDataType::Vec2:		return 4 * 2;
		case ShaderDataType::Vec3:		return 4 * 3;
		case ShaderDataType::Vec4:		return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::IVec2:		return 4 * 2;
		case ShaderDataType::IVec3:		return 4 * 3;
		case ShaderDataType::IVec4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}

		SF_ENGINE_LOG_WARNING("Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement {
		std::string m_name;
		ShaderDataType m_type;
		uint32_t m_size;
		uint32_t m_offset;
		bool m_normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: m_name(name), m_type(type), m_size(CalculateDataTypeSize(type)), m_offset(0), m_normalized(normalized)
		{}

		uint32_t GetComponentCount() const {
			switch (m_type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Vec2:		return 2;
			case ShaderDataType::Vec3:		return 3;
			case ShaderDataType::Vec4:		return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::IVec2:		return 2;
			case ShaderDataType::IVec3:		return 3;
			case ShaderDataType::IVec4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}

			SF_ENGINE_LOG_WARNING("Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) 
			: m_elements(elements)
		{
			CalculateOffsetsAndStride();
		};

		inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
		inline uint32_t GetStride() const { return m_stride; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_stride = 0;

			for (int i = 0; i < m_elements.size(); i++) {
				m_elements[i].m_offset = offset;
				offset += m_elements[i].m_size;
				m_stride += m_elements[i].m_size;
			}
		}

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const  = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual uint32_t GetSize() const = 0;
		virtual uint32_t GetCount() const = 0;

		static sptr<VertexBuffer> Create(uint32_t size);
		static sptr<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;
		virtual IndexElementType GetElementType() const = 0;

		//only supports 32 bit index buffers
		static sptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}