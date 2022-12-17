//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLRendererAPI.h - header file for the class that makes handles the rendering for the OpenGL API
#pragma once

#include "SoulFire/Renderer/RendererAPI.h"
namespace SoulFire {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();

		void Init() override;
		
		void SetClearColor(const glm::vec4& color) override;

		void Clear(RendererEnums::ClearFlags flags) override;
		void Clear(RendererEnums::ClearFlags flags, float depthClearValue) override;
		void Clear(RendererEnums::ClearFlags flags, const glm::vec4& color, float depthClearValue) override;

		void Draw(const sptr<VertexArrayObject>& VAO, uint32_t indexCount = 0) override;

		void UseDepthTest(bool useDepth) override;

		void SetDepthFunc(RendererEnums::DepthFunctions depthfunc) override;

		void UseCulling(bool useCulling) override;

		void SetCullMode(RendererEnums::CullModes mode) override;

		void UseBlending(bool useBlending) override;

		void SetBlendFunc(RendererEnums::BlendFuncSrc src, RendererEnums::BlendFuncDst dst) override;

		TextureLimits GetTextureLimits() override;

		void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	private:
		glm::vec4 m_clearColor;

		TextureLimits m_textureLimits;
	};
}