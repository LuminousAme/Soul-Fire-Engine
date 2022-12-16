//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Rendercommand.h - header file for the class that allows the engine and client to make calls to the renderer
#pragma once

#include "RendererAPI.h"

namespace SoulFire {
	class RenderCommand {
	public:
		inline static void Init() { s_RendererAPI->Init(); }

		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }

		inline static void Clear(int flags) { s_RendererAPI->Clear((RendererEnums::ClearFlags)flags); }
		inline static void Clear(int flags, float depthClearValue) { s_RendererAPI->Clear((RendererEnums::ClearFlags)flags, depthClearValue); }
		inline static void Clear(int flags, const glm::vec4& color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), float depthClearValue = 1.0f) { s_RendererAPI->Clear((RendererEnums::ClearFlags)flags, color, depthClearValue); }

		inline static void Draw(const sptr<VertexArrayObject>& VAO) { s_RendererAPI->Draw(VAO); }

		inline static void UseDepthTest(bool useDepth) { s_RendererAPI->UseDepthTest(useDepth); }
		inline static void SetDepthFunction(RendererEnums::DepthFunctions depthfunc) { s_RendererAPI->SetDepthFunc(depthfunc); }

		inline static void UseCulling(bool useCulling) { s_RendererAPI->UseCulling(useCulling); }
		inline static void SetCullMode(RendererEnums::CullModes mode) { s_RendererAPI->SetCullMode(mode); }

		inline static void UseBlending(bool useBlending) { s_RendererAPI->UseBlending(useBlending); }
		inline static void SetBlendFunc(RendererEnums::BlendFuncSrc src, RendererEnums::BlendFuncDst dst) { s_RendererAPI->SetBlendFunc(src, dst); }

		inline static TextureLimits GetTextureLimits() { s_RendererAPI->GetTextureLimits(); }

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewPort(x, y, width, height); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}