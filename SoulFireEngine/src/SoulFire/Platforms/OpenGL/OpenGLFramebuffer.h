//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLFramebuffer.h - header file for the class that represnets framebuffers for the OpenGL 3 API 
#pragma once

#include "SoulFire/Renderer/Framebuffer.h"
#include "glad/glad.h"

namespace SoulFire {
	struct OpenGLDepthTarget {
		~OpenGLDepthTarget();
		void Unload();
		uint32_t m_textureHandle;
	};

	struct OpenGLColorTarget {
		~OpenGLColorTarget();
		void Unload();
		std::vector<uint32_t> m_textureHandles;
		std::vector<uint32_t> m_formats;
		std::vector<uint32_t> m_buffers;
		unsigned int m_numAttachments = 0;
	};

	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec, bool withDepth, uint32_t colorBuffers, uint32_t format);
		virtual ~OpenGLFramebuffer();

		virtual const FramebufferSpecification& GetSpecification() const { return m_spec; }

		void Unload();

		void Init();

		virtual void AddDepthTarget() override;

		virtual void AddColorTarget(uint32_t format) override;

		virtual void Bind() override;

		virtual void UnBind() override;

		virtual void Clear() override;

		virtual void Resize(const uint32_t& width, const uint32_t& height) override;

		virtual void SetViewport() const;

		virtual uint32_t GetColorAttachmentHandle(uint32_t index) override;

		void Recreate();
	private:
		FramebufferSpecification m_spec; 
		uint32_t m_handle;

		OpenGLDepthTarget m_depth;
		OpenGLColorTarget m_color;
		GLbitfield m_clearFlag = 0;

		bool m_isInit = false;
		bool m_depthActive = false;

		bool CheckFBO();
	};
}