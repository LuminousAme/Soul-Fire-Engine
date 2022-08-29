//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//RendererEnums.h - header file for the class that contains the enums to interface with the renderer
#pragma once

namespace SoulFire {
	//Enums for interacting with the RendererAPI
	class RendererEnums {
	public:
		enum ClearFlags {
			ClearColorBuffer = 1 << 0,
			ClearDepthBuffer = 1 << 1,
			ClearAccumulationBuffer = 1 << 2,
			ClearStencilBuffer = 1 << 3
		};

		enum class DepthFunctions {
			Never = 0, Less, LessEqual, Equal, GreaterEqual, DepthGreater, DepthNotEqual, Always
		};

		enum class CullModes {
			Back = 0, Front, FrontAndBack
		};

		enum class BlendFuncSrc {
			Zero = 0, One, DstColor, OneMinusDstColor, SrcAlpha, OneMinusSrcAlpha, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
		};

		enum class BlendFuncDst {
			Zero = 0, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstAlpha, OneMinusDstAlpha
		};
	};

	//limits of for textures
	struct TextureLimits {
		int maxTextureSize;
		int maxTextureUnits;
		int max3DTextureSize;
		int textureImageUnits;
		float maxAnisotropy;
	};
}