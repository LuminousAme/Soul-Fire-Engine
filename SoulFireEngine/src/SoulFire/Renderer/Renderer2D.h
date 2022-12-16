//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer2D.h - header file for the class that represnets a 2D renderer that can interface with different API 
#pragma once

#include "SoulFire/Renderer/Camera.h"
#include "SoulFire/Renderer/Texture.h"

namespace SoulFire {
	struct TextureProps {
		glm::vec4 tint = glm::vec4(1.0f);
		int tilingFactor = 1.0f;
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginRenderPass(const sptr<Camera>& cam);
		static void EndRenderPass();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const sptr<Texture2D>& texture, const TextureProps& props = TextureProps());
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const sptr<Texture2D>& texture, const TextureProps& props = TextureProps());

		static void DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const sptr<Texture2D>& texture, const TextureProps& props = TextureProps());
		static void DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const sptr<Texture2D>& texture, const TextureProps& props = TextureProps());
	};
}