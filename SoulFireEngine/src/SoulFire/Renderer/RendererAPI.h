//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//RendererAPI.h - header file for the class that makes calls to the various rendering APIs
#pragma once

#include "SF_PCH.h"
#include "VertexArrayObject.h"
#include "RendererEnums.h"

namespace SoulFire {
	class RendererAPI {
	public:
		enum class API {
			NONE = 0, OPENGL
		};
	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void Clear(RendererEnums::ClearFlags flags) = 0;
		virtual void Clear(RendererEnums::ClearFlags flags, float depthClearValue) = 0;
		virtual void Clear(RendererEnums::ClearFlags flags, const glm::vec4& color, float depthClearValue = 1.0f) = 0;
		
		virtual void Draw(const sptr<VertexArrayObject>& VAO) = 0;

		virtual void UseDepthTest(bool useDepth) = 0;

		virtual void SetDepthFunc(RendererEnums::DepthFunctions depthfunc) = 0;

		virtual void UseCulling(bool useCulling) = 0;

		virtual void SetCullMode(RendererEnums::CullModes mode) = 0;

		virtual void UseBlending(bool useBlending) = 0;

		virtual void SetBlendFunc(RendererEnums::BlendFuncSrc src, RendererEnums::BlendFuncDst dst) = 0;

		virtual TextureLimits GetTextureLimits() = 0;

		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}