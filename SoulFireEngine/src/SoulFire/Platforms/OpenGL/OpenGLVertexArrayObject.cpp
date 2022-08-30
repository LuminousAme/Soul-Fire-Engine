//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLVertexArrayObject.cpp - source file for the class that represnets a vertex array object in the OpenGL API

#include "SF_PCH.h"
#include "OpenGLVertexArrayObject.h"

namespace SoulFire {

	static GLenum ShaderDataTypeToOpenGLNativeType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Vec2:		return GL_FLOAT;
		case ShaderDataType::Vec3:		return GL_FLOAT;
		case ShaderDataType::Vec4:		return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::IVec2:		return GL_INT;
		case ShaderDataType::IVec3:		return GL_INT;
		case ShaderDataType::IVec4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		SF_ENGINE_LOG_ASSERT(false, "Unknown ShaderDataType");
		return GL_NONE;
	}

	OpenGLVertexArrayObject::OpenGLVertexArrayObject()
		: m_IBO(nullptr), m_handle(0), m_vertexCount(0)
	{
		glCreateVertexArrays(1, &m_handle);
	}

	OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
	{
		if (m_handle != 0) {
			glDeleteVertexArrays(1, &m_handle);
			m_handle = 0;
		}
	}

	void OpenGLVertexArrayObject::Bind() const
	{
		glBindVertexArray(m_handle);
	}

	void OpenGLVertexArrayObject::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArrayObject::AddVertexBuffer(const sptr<VertexBuffer>& vbo)
	{
		SF_ENGINE_LOG_ASSERT(vbo->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		if (m_vertexCount == 0) {
			m_vertexCount = vbo->GetCount();
		}
		else {
			SF_ENGINE_LOG_ASSERT(vbo->GetCount() != m_vertexCount, "All VBOs bound to a VAO must be of equal size in this implementation");
		}

		Bind();

		vbo->Bind();

		uint32_t index = 0;
		const auto& layout = vbo->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLNativeType(element.m_type),
				element.m_normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(size_t)element.m_offset);
			index++;
		}

		m_VBOs.push_back(vbo);

		UnBind();
	}

	void OpenGLVertexArrayObject::SetIndexBuffer(const sptr<IndexBuffer>& ibo)
	{
		Bind();
		m_IBO = ibo;

		if (m_IBO != nullptr) m_IBO->Bind();
		else glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		UnBind();
	}
}
