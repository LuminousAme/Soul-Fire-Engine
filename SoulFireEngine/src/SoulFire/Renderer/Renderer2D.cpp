//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer2D.cpp - source file for the class that represnets a 2D renderer that can interface with different API 

#include "SF_PCH.h"
#include "Renderer2D.h"

#include "SoulFire/Renderer/VertexArrayObject.h"
#include "SoulFire/Renderer/Shader.h"
#include "SoulFire/Renderer/RenderCommand.h"

namespace SoulFire {
	struct Renderer2DData {
		sptr<VertexArrayObject> vao;
		sptr<Shader> textureShader;
		sptr<Texture> whiteTexture;
	};

	static Renderer2DData* s_Data2D;

	void Renderer2D::Init()
	{
		s_Data2D = new Renderer2DData();

		s_Data2D->vao = VertexArrayObject::Create();

		float squareVertices[4 * 5] = {
			-0.5f,	 -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f,	 -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,    0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,    0.5f,  0.0f, 0.0f, 1.0f
		};
		sptr<VertexBuffer> sqaureVBO;
		sqaureVBO = SoulFire::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		sqaureVBO->SetLayout({
			{ ShaderDataType::Vec3, "inPosition" },
			{ ShaderDataType::Vec2, "inUv" },
			});
		s_Data2D->vao->AddVertexBuffer(sqaureVBO);

		uint32_t sqaureIndices[6] = { 0, 1, 2, 2, 3, 0 };
		sptr<IndexBuffer> sqaureIBO;
		sqaureIBO = IndexBuffer::Create(sqaureIndices, sizeof(sqaureIndices) / sizeof(uint32_t));
		s_Data2D->vao->SetIndexBuffer(sqaureIBO);

		s_Data2D->whiteTexture = SoulFire::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data2D->whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Data2D->textureShader = SoulFire::Shader::Create("Simple Texture Shader");
		s_Data2D->textureShader->LoadFullShaderFromFile("assets/shaders/texture.glsl");
		s_Data2D->textureShader->Link();
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data2D;
	}

	void Renderer2D::BeginRenderPass(const sptr<Camera>& cam)
	{
		s_Data2D->textureShader->Bind();
		s_Data2D->textureShader->SetUniformMatrix("u_ViewProjection", cam->GetVP());
	}

	void Renderer2D::EndRenderPass()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data2D->textureShader->SetUniform("u_color", color);
		s_Data2D->textureShader->SetUniform("u_tilingFactor", 1.0f);

		glm::mat4 trans = glm::translate(pos) * glm::scale(glm::vec3(size.x, size.y, 1.0f));
		s_Data2D->textureShader->SetUniformMatrix("u_Model", trans);

		s_Data2D->whiteTexture->Bind(0);

		s_Data2D->vao->Bind();
		RenderCommand::Draw(s_Data2D->vao);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, texture, props);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		s_Data2D->textureShader->SetUniform("u_color", props.tint);
		s_Data2D->textureShader->SetUniform("u_tilingFactor", props.tilingFactor);

		glm::mat4 trans = glm::translate(pos) * glm::scale(glm::vec3(size.x, size.y, 1.0f));
		s_Data2D->textureShader->SetUniformMatrix("u_Model", trans);

		texture->Bind(0);

		s_Data2D->vao->Bind();
		RenderCommand::Draw(s_Data2D->vao);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(pos.x, pos.y, 0.0f), size, rotDegrees, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const glm::vec4& color)
	{
		s_Data2D->textureShader->SetUniform("u_color", color);
		s_Data2D->textureShader->SetUniform("u_tilingFactor", 1.0f);

		glm::mat4 trans = glm::translate(pos) * 
			glm::toMat4(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rotDegrees)))) * 
			glm::scale(glm::vec3(size.x, size.y, 1.0f));
		s_Data2D->textureShader->SetUniformMatrix("u_Model", trans);

		s_Data2D->whiteTexture->Bind(0);

		s_Data2D->vao->Bind();
		RenderCommand::Draw(s_Data2D->vao);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		DrawRotatedQuad(glm::vec3(pos.x, pos.y, 0.0f), size, rotDegrees, texture, props);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		s_Data2D->textureShader->SetUniform("u_color", props.tint);
		s_Data2D->textureShader->SetUniform("u_tilingFactor", props.tilingFactor);

		glm::mat4 trans = glm::translate(pos) *
			glm::toMat4(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rotDegrees)))) *
			glm::scale(glm::vec3(size.x, size.y, 1.0f));
		s_Data2D->textureShader->SetUniformMatrix("u_Model", trans);

		texture->Bind(0);

		s_Data2D->vao->Bind();
		RenderCommand::Draw(s_Data2D->vao);
	}
}