//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLTexture.cpp - source file for the classes that represent textures in the OpenGL API

#include "SF_PCH.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace SoulFire {
	bool OpenGLTexture2D::s_init = false;
	float OpenGLTexture2D::s_maxAnisotropy = 0.0f;

	static uint32_t ConvertMinFilter(SoulFire::Texture2D::Filter filter) {
		switch (filter)
		{
		case SoulFire::Texture2D::Filter::Nearest:
			return GL_NEAREST;
			break;
		case SoulFire::Texture2D::Filter::Linear:
			return GL_LINEAR;
			break;
		case SoulFire::Texture2D::Filter::NearestMipNearest:
			return GL_NEAREST_MIPMAP_NEAREST;
			break;
		case SoulFire::Texture2D::Filter::LinearMipNearest:
			return GL_LINEAR_MIPMAP_NEAREST;
			break;
		case SoulFire::Texture2D::Filter::NearestMipLinear:
			return GL_NEAREST_MIPMAP_LINEAR;
			break;
		case SoulFire::Texture2D::Filter::LinearMipLinear:
			return GL_LINEAR_MIPMAP_LINEAR;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Min filter not supported!")
				break;
		}

		return 0;
	}

	static uint32_t ConvertMagFilter(SoulFire::Texture2D::Filter filter) {
		switch (filter)
		{
		case SoulFire::Texture2D::Filter::Nearest:
			return GL_NEAREST;
			break;
		case SoulFire::Texture2D::Filter::Linear:
			return GL_LINEAR;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Mag filter not supported!")
				break;
		}

		return 0;
	}

	static uint32_t ConvertWrapMode(SoulFire::Texture2D::WrapMode mode) {
		switch (mode)
		{
		case SoulFire::Texture2D::WrapMode::ClampToEdge:
			return GL_CLAMP_TO_EDGE;
			break;
		case SoulFire::Texture2D::WrapMode::ClmapToBorder:
			return GL_CLAMP_TO_BORDER;
			break;
		case SoulFire::Texture2D::WrapMode::MirroredRepeat:
			return GL_MIRRORED_REPEAT;
			break;
		case SoulFire::Texture2D::WrapMode::Repeat:
			return GL_REPEAT;
			break;
		case SoulFire::Texture2D::WrapMode::MirrorClampToEdge:
			return GL_MIRROR_CLAMP_TO_EDGE;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Wrap Mode not supported!");
			break;
		}

		return 0;
	}

	OpenGLTexture2D::OpenGLTexture2D(std::string filepath, bool generateMipmaps)
		: m_filepath(filepath), m_handle(0)
	{
		if (!s_init) {
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &s_maxAnisotropy);
			s_init = true;
		}

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		SF_ENGINE_LOG_ASSERT(data, "Failed to load image at {0}!", filepath);
		SF_ENGINE_LOG_ASSERT(width * height > 0, "No pixels in image at {0}", filepath);

		uint32_t internal_format;
		uint32_t image_format;
		switch (channels) {
		case 1:
			internal_format = GL_R8;
			image_format = GL_RED;
			break;
		case 2:
			internal_format = GL_RG8;
			image_format = GL_RG;
			break;
		case 3:
			internal_format = GL_RGB8;
			image_format = GL_RGB;
			break;
		case 4:
			internal_format = GL_RGBA8;
			image_format = GL_RGBA;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Unsupported texture format");
			break;
		}

		m_internalFormat = internal_format;
		m_imageFormat = image_format;

		m_width = width;
		m_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
		glTextureStorage2D(m_handle, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, ConvertMinFilter(m_minFilter));
		glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, ConvertMagFilter(m_magFilter));

		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, ConvertWrapMode(m_horiWrapMode));
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, ConvertWrapMode(m_vertWrapMode));

		glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, m_imageFormat, GL_UNSIGNED_BYTE, data);

		m_minimaps = generateMipmaps;
		if (m_minimaps) {
			glGenerateTextureMipmap(m_handle);
		}

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(const int& width, const int& height)
		: m_width(width), m_height(height), m_internalFormat(GL_RGBA8), m_imageFormat(GL_RGBA)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
		glTextureStorage2D(m_handle, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, ConvertMinFilter(m_minFilter));
		glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, ConvertMagFilter(m_magFilter));

		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, ConvertWrapMode(m_horiWrapMode));
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, ConvertWrapMode(m_vertWrapMode));
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_handle);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, m_imageFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_handle);
	}

	void OpenGLTexture2D::UnBind(uint32_t slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture2D::SetAnisotropicFiltering(const float& level)
	{
		float l = level;
		if (l < 0.0f) l = s_maxAnisotropy;
		m_anisotropy = l;
		if(m_handle != 0) glTextureParameterf(m_handle, GL_TEXTURE_MAX_ANISOTROPY, m_anisotropy);
	}

	void OpenGLTexture2D::UpdateMinFilter()
	{
		if (m_handle != 0) glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, ConvertMinFilter(m_minFilter));
	}

	void OpenGLTexture2D::UpdateMagFilter()
	{
		if(m_handle != 0) glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, ConvertMagFilter(m_magFilter));
	}

	void OpenGLTexture2D::UpdateHoriWrap()
	{

		if(m_handle != 0) glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, ConvertWrapMode(m_horiWrapMode));
	}

	void OpenGLTexture2D::UpdateVertWrap()
	{
		if(m_handle != 0) glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, ConvertWrapMode(m_vertWrapMode));
	}
}