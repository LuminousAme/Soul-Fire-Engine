//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLFramebuffer.cpp - header file for the class that represnets framebuffers for the OpenGL 3 API 

#include "SF_PCH.h"
#include "OpenGLFramebuffer.h"

namespace SoulFire {
	static const uint32_t s_MaxFramebufferSize = 8192;

	OpenGLDepthTarget::~OpenGLDepthTarget()
	{
		Unload();
	}

	void OpenGLDepthTarget::Unload()
	{
		GLuint handle = (GLuint)m_textureHandle;
		glDeleteTextures(1, &handle);
	}

	OpenGLColorTarget::~OpenGLColorTarget()
	{
		Unload();
	}

	void OpenGLColorTarget::Unload()
	{
		for (uint32_t i = 0; i < m_numAttachments; i++) {
			GLuint handle = (GLuint)m_textureHandles[i];
			glDeleteTextures(1, &handle);
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec, bool withDepth, uint32_t colorBuffers, uint32_t format)
		: m_spec(spec)
	{
		if (withDepth) AddDepthTarget();

		for (uint32_t i = 0; i < colorBuffers; i++) AddColorTarget(format);

		Init();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		Unload();
		m_color.Unload();
		m_depth.Unload();
	}

	void OpenGLFramebuffer::Unload()
	{
		glDeleteFramebuffers(1, &m_handle);
		m_isInit = false;
	}

	void OpenGLFramebuffer::Init()
	{
		glGenFramebuffers(1, &m_handle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);

		if (m_depthActive)
		{
			m_clearFlag |= GL_DEPTH_BUFFER_BIT;

			glGenTextures(1, &m_depth.m_textureHandle);
			glBindTexture(GL_TEXTURE_2D, m_depth.m_textureHandle);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, m_spec.Width, m_spec.Height);

			glTextureParameteri(m_depth.m_textureHandle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_depth.m_textureHandle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(m_depth.m_textureHandle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(m_depth.m_textureHandle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth.m_textureHandle, 0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		if (m_color.m_numAttachments)
		{
			m_clearFlag |= GL_COLOR_BUFFER_BIT;
			GLuint* textureHandles = new GLuint[m_color.m_numAttachments];

			glGenTextures(m_color.m_numAttachments, textureHandles);

			//Loops through them
			for (unsigned i = 0; i < m_color.m_numAttachments; i++)
			{
				//set the handle
				m_color.m_textureHandles[i] = textureHandles[i];

				//Binds the texture
				glBindTexture(GL_TEXTURE_2D, m_color.m_textureHandles[i]);
				//Sets the texture storage
				glTexStorage2D(GL_TEXTURE_2D, 1, m_color.m_formats[i], m_spec.Width, m_spec.Height);

				//Set texture parameters
				glTextureParameteri(m_color.m_textureHandles[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTextureParameteri(m_color.m_textureHandles[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTextureParameteri(m_color.m_textureHandles[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTextureParameteri(m_color.m_textureHandles[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				//Sets up as a framebuffer texture
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_color.m_textureHandles[i], 0);
			}

			delete[] textureHandles;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
		m_isInit = true;
	}

	void OpenGLFramebuffer::AddDepthTarget()
	{
		//if there is a handle already, unload it
		if (m_depth.m_textureHandle)
		{
			m_depth.Unload();
		}
		//Make depth active true
		m_depthActive = true;
	}

	void OpenGLFramebuffer::AddColorTarget(uint32_t format)
	{
		m_color.m_textureHandles.resize(m_color.m_numAttachments + 1);
		m_color.m_formats.push_back(format);
		m_color.m_buffers.push_back(GL_COLOR_ATTACHMENT0 + m_color.m_numAttachments);
		m_color.m_numAttachments++;
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);

		if (m_color.m_numAttachments)
		{
			glDrawBuffers(m_color.m_numAttachments, &m_color.m_buffers[0]);
		}
	}

	void OpenGLFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
	}

	void OpenGLFramebuffer::Clear()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
		glClear(m_clearFlag);
		glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
	}

	void OpenGLFramebuffer::Resize(const uint32_t& width, const uint32_t& height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize) {
			SF_ENGINE_LOG_WARNING("Attempted to resize framebuffer to {0}, {1}. Acceptable range is 1-{2}", width, height, s_MaxFramebufferSize);
			return;
		}

		m_spec.Width = width;
		m_spec.Height = height;
		Recreate();
	}

	void OpenGLFramebuffer::SetViewport() const
	{
		glViewport(0, 0, m_spec.Width, m_spec.Height);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentHandle(uint32_t index)
	{
		if(index >= m_color.m_numAttachments) return 0;
		return m_color.m_textureHandles[index];
	}

	void OpenGLFramebuffer::Recreate()
	{
		Unload();
		m_depth.Unload();
		m_color.Unload();
		Init();
	}

	bool OpenGLFramebuffer::CheckFBO()
	{
		//Binds the framebuffer
		Bind();
		//Check the framebuffer status
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			SF_ENGINE_LOG_ERROR("Framebuffer is not correctly set up");
			return false;
		}
		return true;
	}



}