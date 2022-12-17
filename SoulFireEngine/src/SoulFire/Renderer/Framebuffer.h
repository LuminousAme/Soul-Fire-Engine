//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Framebuffer.h - header file for the classes that represent framebuffers regardless of API
#pragma once

#include "SF_PCH.h"
#include "Texture.h"

namespace SoulFire {
	struct FramebufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static sptr<Framebuffer> Create(const FramebufferSpecification& spec, bool withDepth = true, uint32_t colorBuffers = 1, uint32_t format = 0x8058);

		virtual void AddDepthTarget() = 0;
		virtual void AddColorTarget(uint32_t format) = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Clear() = 0;
		virtual void Resize(const uint32_t& width, const uint32_t& height) = 0;
		virtual void SetViewport() const = 0;

		virtual uint32_t GetColorAttachmentHandle(uint32_t index) = 0;
	};
}