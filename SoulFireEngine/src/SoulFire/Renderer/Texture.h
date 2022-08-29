//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Texture.h - header file for the classes that represent textures regardless of API
#pragma once

#include "SF_PCH.h"
#include "RenderCommand.h"

namespace SoulFire {
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void UnBind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default;

		static sptr<Texture2D> Create(const std::string& filepath, bool generateMipmaps = false);

		enum class Filter {
			None = 0,
			Nearest,
			Linear,
			NearestMipNearest,
			LinearMipNearest,
			NearestMipLinear,
			LinearMipLinear
		};

		enum class WrapMode {
			None = 0,
			ClampToEdge,
			ClmapToBorder,
			MirroredRepeat,
			Repeat,
			MirrorClampToEdge
		};

		void SetMinFilter(const Filter& min) { m_minFilter = min; UpdateMinFilter(); }
		Filter GetMinFilter() const { return m_minFilter; }

		void SetMagFilter(const Filter& mag) { m_magFilter = mag; UpdateMagFilter(); }
		Filter GetMagFilter() const { return m_magFilter; }

		void SetHorizontalWrapMode(const WrapMode& mode) { m_horiWrapMode = mode; UpdateHoriWrap(); }
		WrapMode GetHorizontalWrapMode() const { return m_horiWrapMode; }

		void SetVerticalWrapMode(const WrapMode& mode) { m_vertWrapMode = mode; UpdateHoriWrap(); }
		WrapMode GetVerticalWrapMode() const { return m_vertWrapMode; }

		virtual void SetAnisotropicFiltering(const float& level) = 0;

	protected:
		virtual void UpdateMinFilter() = 0;
		virtual void UpdateMagFilter() = 0;
		virtual void UpdateHoriWrap() = 0;
		virtual void UpdateVertWrap() = 0;

	protected:
		Filter m_minFilter = Filter::Linear;
		Filter m_magFilter = Filter::Linear;
		WrapMode m_horiWrapMode = WrapMode::Repeat;
		WrapMode m_vertWrapMode = WrapMode::Repeat;
		float m_anisotropy = -1.0f;
		bool m_minimaps;
	};
}