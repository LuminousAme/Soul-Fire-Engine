//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Compoents.h - header file for the various structs that represents components
#pragma once

#include "SF_PCH.h"
#include "SoulFire/Renderer/Texture.h"
#include "SoulFire/Renderer/SubTexture2D.h"

namespace SoulFire {
	struct InfoComponent {
		std::string m_name = "Entity";
		std::string m_tag;

		InfoComponent() = default;
		InfoComponent(const InfoComponent&) = default;
		InfoComponent(const std::string& name, const std::string& tag = std::string())
			: m_name(name), m_tag(tag) {}
	};

	struct Transform {
		glm::mat4 m_transform {1.0f};

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const glm::mat4& transform)
			: m_transform(transform) {}

		operator glm::mat4&() { return m_transform; }
		operator const glm::mat4& () { return m_transform; }
	};

	struct SpriteRenderer {
		glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		sptr<Texture2D> m_fullsprite;
		sptr<SubTexture2D> m_subsprite;
		float m_tilingFactor = 1.0f;

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const glm::vec4& color)
			: m_color(color), m_fullsprite(nullptr), m_subsprite(nullptr), m_tilingFactor(1.0f) {
		}

		SpriteRenderer(sptr<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const float tilingFactor = 1.0f)
			:m_color(color), m_fullsprite(texture), m_subsprite(nullptr), m_tilingFactor(tilingFactor) {
		}

		SpriteRenderer(sptr<SubTexture2D> subtexture, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const float tilingFactor = 1.0f)
			: m_color(color), m_fullsprite(nullptr), m_subsprite(subtexture), m_tilingFactor(tilingFactor) {
		}
	};
}