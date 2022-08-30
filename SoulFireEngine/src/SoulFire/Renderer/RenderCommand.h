//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Rendercommand.h - header file for the class that allows the engine and client to make calls to the renderer
#pragma once

#include "RendererAPI.h"

namespace SoulFire {
	class RenderCommand {
	public:
		inline static void Init() { s_RendererAPI->Init(); }

		inline static void Clear(int flags, const glm::vec4& color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)) { s_RendererAPI->Clear((RendererEnums::ClearFlags)flags, color); }

		inline static void Draw(const sptr<VertexArrayObject>& VAO) { s_RendererAPI->Draw(VAO); }

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewPort(x, y, width, height); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}