//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SubTexture.cpp - spurce file for the class that represent a single part of a texture Atlas

#include "SF_PCH.h"
#include "SubTexture2D.h"

namespace SoulFire {
	SubTexture2D::SubTexture2D(const sptr<Texture2D>& texture, const glm::vec2& minUV, const glm::vec2& maxUV)
		: m_texture(texture)
	{
		m_Uvs[0] = { minUV.x, minUV.y };
		m_Uvs[1] = { maxUV.x, minUV.y };
		m_Uvs[2] = { maxUV.x, maxUV.y };
		m_Uvs[3] = { minUV.x, maxUV.y };
	}

	sptr<SubTexture2D> SubTexture2D::CreateFromCoordinates(const sptr<Texture2D>& texture, const glm::vec2& index, const glm::vec2& indivualSpriteSize, const glm::vec2& spriteScale)
	{
		glm::vec2 min = { (index.x * indivualSpriteSize.x) / texture->GetWidth(), (index.y * indivualSpriteSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((index.x + spriteScale.x) * indivualSpriteSize.x) / texture->GetWidth(), ((index.y + spriteScale.y) * indivualSpriteSize.y) / texture->GetHeight()};
		return std::make_shared<SubTexture2D>(texture, min, max);
	}

	sptr<SubTexture2D> SubTexture2D::CreateFromPixelOffset(const sptr<Texture2D>& texture, const glm::vec2& pixelOffset, const glm::vec2& thisSpriteSize)
	{
		glm::vec2 min = { pixelOffset.x / texture->GetWidth(), pixelOffset.y / texture->GetHeight() };
		glm::vec2 max = min + glm::vec2(thisSpriteSize.x / texture->GetWidth(), thisSpriteSize.y / texture->GetHeight());
		return std::make_shared<SubTexture2D>(texture, min, max);
	}
}

