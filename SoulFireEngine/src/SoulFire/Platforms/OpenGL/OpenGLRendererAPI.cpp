//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLRendererAPI.cpp - source file for the class that makes handles the rendering for the OpenGL API

#include "SF_PCH.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace SoulFire {
	static GLenum IndexElementTypeToOpenGLNativeType(IndexElementType type) {
		switch (type) {
		case IndexElementType::UNSIGNEDINT:		return GL_UNSIGNED_INT;
		}

		SF_ENGINE_LOG_ASSERT(false, "Unknown IndexElementType");
		return GL_NONE;
	}

	OpenGLRendererAPI::OpenGLRendererAPI()
		: m_clearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f))
	{
	}

	void OpenGLRendererAPI::Init()
	{
		//log the opengl version being used
		SF_ENGINE_LOG_INFO(glGetString(GL_VERSION));

		//get some info on the limits of the renderer and log them
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_textureLimits.maxTextureSize);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_textureLimits.maxTextureUnits);
		glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &m_textureLimits.max3DTextureSize);
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_textureLimits.textureImageUnits);
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &m_textureLimits.maxAnisotropy);

		//log that info
		SF_ENGINE_LOG_INFO("--- Texture Limits ---");
		SF_ENGINE_LOG_INFO("\tSize:       {0}", m_textureLimits.maxTextureSize);
		SF_ENGINE_LOG_INFO("\tUnits:      {0}", m_textureLimits.maxTextureUnits);
		SF_ENGINE_LOG_INFO("\t3D Size:    {0}", m_textureLimits.max3DTextureSize);
		SF_ENGINE_LOG_INFO("\tUnits (FS): {0}", m_textureLimits.textureImageUnits);
		SF_ENGINE_LOG_INFO("\tMax Aniso:  {0}", m_textureLimits.maxAnisotropy);

		//enable depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//enable face culling, back face by default
		glEnable(GL_CULL_FACE);

		//enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::Clear(RendererEnums::ClearFlags flags, const glm::vec4& color, float depthClearValue)
	{
		if (color != m_clearColor) {
			m_clearColor = color;
			glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		}

		depthClearValue = glm::clamp(depthClearValue, 0.0f, 1.0f);
		glClearDepth(depthClearValue);

		GLenum clearFlag = 0;
		if (flags & RendererEnums::ClearColorBuffer) clearFlag |= GL_COLOR_BUFFER_BIT;
		if (flags & RendererEnums::ClearDepthBuffer) clearFlag |= GL_DEPTH_BUFFER_BIT;
		if (flags & RendererEnums::ClearAccumulationBuffer) clearFlag |= GL_ACCUM_BUFFER_BIT;
		if (flags & RendererEnums::ClearStencilBuffer) clearFlag |= GL_STENCIL_BUFFER_BIT;
		glClear(clearFlag);
	}

	void OpenGLRendererAPI::Draw(const sptr<VertexArrayObject>& VAO)
	{
		VAO->Bind();
		if (VAO->GetIndexBuffer() != nullptr) {
			glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), IndexElementTypeToOpenGLNativeType(VAO->GetIndexBuffer()->GetElementType()), nullptr);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, VAO->GetVertexCount());
		}
		VAO->UnBind();
	}

	void OpenGLRendererAPI::UseDepthTest(bool useDepth)
	{
		if (useDepth) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetDepthFunction(RendererEnums::DepthFunctions depthfunc)
	{
		GLenum depthFunc = 0;

		switch (depthfunc)
		{
		case SoulFire::RendererEnums::DepthFunctions::Never:
			depthFunc = GL_NEVER;
			break;
		case SoulFire::RendererEnums::DepthFunctions::Less:
			depthFunc = GL_LESS;
			break;
		case SoulFire::RendererEnums::DepthFunctions::LessEqual:
			depthFunc = GL_LEQUAL;
			break;
		case SoulFire::RendererEnums::DepthFunctions::Equal:
			depthFunc = GL_EQUAL;
			break;
		case SoulFire::RendererEnums::DepthFunctions::GreaterEqual:
			depthFunc = GL_GEQUAL;
			break;
		case SoulFire::RendererEnums::DepthFunctions::DepthGreater:
			depthFunc = GL_GREATER;
			break;
		case SoulFire::RendererEnums::DepthFunctions::DepthNotEqual:
			depthFunc = GL_NOTEQUAL;
			break;
		case SoulFire::RendererEnums::DepthFunctions::Always:
			depthFunc = GL_ALWAYS;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Unknown Depth Function supplied!");
			break;
		}

		glDepthFunc(depthFunc);
	}

	void OpenGLRendererAPI::UseCulling(bool useCulling)
	{
		if (useCulling) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
	}

	void OpenGLRendererAPI::SetCullMode(RendererEnums::CullModes mode)
	{
		GLenum cullmode = 0;

		switch (mode)
		{
		case SoulFire::RendererEnums::CullModes::Back:
			cullmode = GL_BACK;
			break;
		case SoulFire::RendererEnums::CullModes::Front:
			cullmode = GL_FRONT;
			break;
		case SoulFire::RendererEnums::CullModes::FrontAndBack:
			cullmode = GL_FRONT_AND_BACK;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Unknown cull mode supplied!");
			break;
		}

		glCullFace(cullmode);
	}

	void OpenGLRendererAPI::UseBlending(bool useBlending)
	{
		if (useBlending) glEnable(GL_BLEND);
		else glDisable(GL_BLEND);
	}

	void OpenGLRendererAPI::SetBlendFunc(RendererEnums::BlendFuncSrc src, RendererEnums::BlendFuncDst dst)
	{
		GLenum srcParam = 0;
		switch (src)
		{
		case SoulFire::RendererEnums::BlendFuncSrc::Zero:
			srcParam = GL_ZERO;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::One:
			srcParam = GL_ONE;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::DstColor:
			srcParam = GL_DST_COLOR;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::OneMinusDstColor:
			srcParam = GL_ONE_MINUS_DST_COLOR;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::SrcAlpha:
			srcParam = GL_SRC_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::OneMinusSrcAlpha:
			srcParam = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::DstAlpha:
			srcParam = GL_DST_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::OneMinusDstAlpha:
			srcParam = GL_ONE_MINUS_DST_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncSrc::SrcAlphaSaturate:
			srcParam = GL_SRC_ALPHA_SATURATE;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Unknown blend func supplied!");
			break;
		}

		GLenum dstParam = 0;
		switch (dst)
		{
		case SoulFire::RendererEnums::BlendFuncDst::Zero:
			dstParam = GL_ZERO;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::One:
			dstParam = GL_ONE;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::SrcColor:
			dstParam = GL_SRC_COLOR;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::OneMinusSrcColor:
			dstParam = GL_ONE_MINUS_SRC_COLOR;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::SrcAlpha:
			dstParam = GL_SRC_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::OneMinusSrcAlpha:
			dstParam = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::DstAlpha:
			dstParam = GL_DST_ALPHA;
			break;
		case SoulFire::RendererEnums::BlendFuncDst::OneMinusDstAlpha:
			dstParam = GL_ONE_MINUS_DST_ALPHA;
			break;
		default:
			SF_ENGINE_LOG_ASSERT(false, "Unknown blend func supplied!");
			break;
		}

		glBlendFunc(srcParam, dstParam);
	}
	TextureLimits OpenGLRendererAPI::GetTextureLimits()
	{
		return m_textureLimits;
	}
}