//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLTexture.h - header file for the classes that represent textures in the OpenGL API
#pragma once

#include "SoulFire/Renderer/Texture.h"
#include "glad/glad.h"

namespace SoulFire {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(std::string filepath, bool generateMipmaps);
		virtual ~OpenGLTexture2D();

		uint32_t GetWidth() const override { return m_width; };
		uint32_t GetHeight() const override { return m_height; };

		void Bind(uint32_t slot = 0) const override;
		void UnBind(uint32_t slot = 0) const override;

		void SetAnisotropicFiltering(const float& level) override;

	private:
		void UpdateMinFilter() override;
		void UpdateMagFilter() override;
		void UpdateHoriWrap() override;
		void UpdateVertWrap() override;

	private:
		std::string m_filepath;
		uint32_t m_width;
		uint32_t m_height;
		GLuint m_handle;

	private:
		static bool s_init;
		static float s_maxAnisotropy;
	};
}