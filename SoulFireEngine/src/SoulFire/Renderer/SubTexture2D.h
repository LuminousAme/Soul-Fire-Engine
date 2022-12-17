//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SubTexture.h - header file for the class that represent a single part of a texture Atlas
#pragma once

#include "Texture.h"

namespace SoulFire {

	class SubTexture2D {
	public:
		SubTexture2D(const sptr<Texture2D>& texture, const glm::vec2& minUV, const glm::vec2& maxUV);
		~SubTexture2D() = default;

		const sptr<Texture2D> GetTexture() const { return m_texture; }
		const glm::vec2* GetUVs() const { return m_Uvs; }

		static sptr<SubTexture2D> CreateFromCoordinates(const sptr<Texture2D>& texture, const glm::vec2& index, const glm::vec2& spriteSize, const glm::vec2& spriteScale = {1.0f, 1.0f});
		static sptr<SubTexture2D> CreateFromPixelOffset(const sptr<Texture2D>& texture, const glm::vec2& pixelOffset, const glm::vec2& thisSpriteSize);
	private:
		sptr<Texture2D> m_texture;
		glm::vec2 m_Uvs[4];
	};
}