//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLRendererAPI.h - header file for the class that makes handles the rendering for the OpenGL API
#pragma once

#include "SoulFire/Renderer/RendererAPI.h"
namespace SoulFire {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();

		void Init() override;

		void Clear(RendererEnums::ClearFlags flags, const glm::vec4& color, float depthClearValue) override;

		void Draw(const sptr<VertexArrayObject>& VAO) override;

		void UseDepthTest(bool useDepth) override;

		void SetDepthFunction(RendererEnums::DepthFunctions depthfunc) override;

		void UseCulling(bool useCulling) override;

		void SetCullMode(RendererEnums::CullModes mode) override;

		void UseBlending(bool useBlending) override;

		void SetBlendFunc(RendererEnums::BlendFuncSrc src, RendererEnums::BlendFuncDst dst) override;

		TextureLimits GetTextureLimits() override;
	private:
		glm::vec4 m_clearColor;

		TextureLimits m_textureLimits;
	};
}