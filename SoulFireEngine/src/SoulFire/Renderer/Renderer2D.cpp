//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer2D.cpp - source file for the class that represnets a 2D renderer that can interface with different API 

#include "SF_PCH.h"
#include "Renderer2D.h"

#include "SoulFire/Renderer/VertexArrayObject.h"
#include "SoulFire/Renderer/Shader.h"
#include "SoulFire/Renderer/RenderCommand.h"

namespace SoulFire {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 Uv;
		float TexIndex = 0;
		float TilingFactor = 1.0f;
	};

	struct Renderer2DData {
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; //eventually replace with data based on GPU query 

		sptr<VertexArrayObject> quadVao;
		sptr<VertexBuffer> quadVBO;
		sptr<Shader> textureShader;
		sptr<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;

		QuadVertex* quadVertexBase = nullptr;
		QuadVertex* quadVertexPtr = nullptr;

		std::array<sptr<Texture2D>, MaxTextureSlots> textureSlots; //eventually use asset guids instead of texture handles
		uint32_t textureSlotIndex = 1;

		glm::vec4 rotatedQuadVertexPositions[4];
	};

	static Renderer2DData s_Data2D;

	void Renderer2D::Init()
	{
		s_Data2D.quadVao = VertexArrayObject::Create();

		
		s_Data2D.quadVBO = SoulFire::VertexBuffer::Create(s_Data2D.MaxVertices * sizeof(QuadVertex));
		s_Data2D.quadVBO->SetLayout({
			{ ShaderDataType::Vec3, "inPosition" },
			{ ShaderDataType::Vec4, "inColor" },
			{ ShaderDataType::Vec2, "inUv" },
			{ ShaderDataType::Float, "inTexIndex" },
			{ ShaderDataType::Float, "inTilingFactor" },
			});
		s_Data2D.quadVao->AddVertexBuffer(s_Data2D.quadVBO);

		s_Data2D.quadVertexBase = new QuadVertex[s_Data2D.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data2D.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data2D.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		sptr<IndexBuffer> sqaureIBO;
		sqaureIBO = IndexBuffer::Create(quadIndices, s_Data2D.MaxIndices);
		s_Data2D.quadVao->SetIndexBuffer(sqaureIBO);
		delete[] quadIndices; //change this to a reference system later, just avoiding shared pointers right now to avoid allocating 60k 32 bit ints on the stack 

		s_Data2D.whiteTexture = SoulFire::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data2D.whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		int samplers[s_Data2D.MaxTextureSlots];
		for (int i = 0; i < s_Data2D.MaxTextureSlots; i++) {
			samplers[i] = i;
		}

		s_Data2D.textureShader = SoulFire::Shader::Create("Simple Texture Shader");
		s_Data2D.textureShader->LoadFullShaderFromFile("assets/shaders/texture.glsl");
		s_Data2D.textureShader->Link();
		s_Data2D.textureShader->Bind();
		s_Data2D.textureShader->SetUniform("s_Textures", samplers, (int)s_Data2D.MaxTextureSlots);
		s_Data2D.textureShader->UnBind();

		for (uint32_t i = 0; i < s_Data2D.textureSlots.size(); i++) s_Data2D.textureSlots[i] = nullptr;
		s_Data2D.textureSlots[0] = s_Data2D.whiteTexture;

		s_Data2D.rotatedQuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data2D.rotatedQuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data2D.rotatedQuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data2D.rotatedQuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginRenderPass(const sptr<Camera>& cam)
	{
		s_Data2D.textureShader->Bind();
		s_Data2D.textureShader->SetUniformMatrix("u_ViewProjection", cam->GetVP());

		//start the first batch
		StartBatch();
	}

	void Renderer2D::EndRenderPass()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		uint32_t dataSize = (uint8_t*)s_Data2D.quadVertexPtr - (uint8_t*)s_Data2D.quadVertexBase;
		s_Data2D.quadVBO->SetData(s_Data2D.quadVertexBase, dataSize);

		//bind textures
		for (uint32_t i = 0; i < s_Data2D.textureSlotIndex; i++) {
			s_Data2D.textureSlots[i]->Bind(i);
		}

		s_Data2D.textureShader->Bind();
		RenderCommand::Draw(s_Data2D.quadVao, s_Data2D.quadIndexCount);
		s_Data2D.textureShader->UnBind();

		//after you finish flushing start the next batch
		StartBatch();
	}

	void Renderer2D::StartBatch()
	{
		for (uint32_t i = 1; i < s_Data2D.textureSlotIndex; i++) {
			s_Data2D.textureSlots[i] = nullptr;
		}

		s_Data2D.quadVertexPtr = s_Data2D.quadVertexBase;
		s_Data2D.quadIndexCount = 0;
		s_Data2D.textureSlotIndex = 1;
	}

	void Renderer2D::CheckShouldFlush()
	{
		//if we've run out of texture slots, flush the batch to start another
		if (s_Data2D.textureSlotIndex >= s_Data2D.MaxTextureSlots) Flush();
		//if we've run out of quads, flush the batch to start another
		else if (s_Data2D.quadIndexCount >= s_Data2D.MaxIndices) Flush();
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		CheckShouldFlush();

		const float texIndex = 0.0f; //all white texture
		const float tilingFactor = 1.0f;

		//bottom left
		s_Data2D.quadVertexPtr->Position = {pos.x - 0.5f * size.x, pos.y - 0.5f * size.y, 0.0f};
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//bottom right
		s_Data2D.quadVertexPtr->Position = { pos.x + 0.5f * size.x, pos.y - 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top right
		s_Data2D.quadVertexPtr->Position = { pos.x + 0.5f * size.x, pos.y + 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top left
		s_Data2D.quadVertexPtr->Position = { pos.x - 0.5f * size.x, pos.y + 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//increase the quad index count
		s_Data2D.quadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, texture, props);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		CheckShouldFlush();

		float textureIndex = 0.0f;

		//check if the texture is already in the draw call and grab it's index if it doesn't
		for (uint32_t i = 1; i < s_Data2D.textureSlotIndex; i++) {
			if (*s_Data2D.textureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if it is not add it and give it a new index
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data2D.textureSlotIndex;
			s_Data2D.textureSlots[s_Data2D.textureSlotIndex] = texture;
			s_Data2D.textureSlotIndex++;
		}

		//bottom left
		s_Data2D.quadVertexPtr->Position = { pos.x - 0.5f * size.x, pos.y - 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//bottom right
		s_Data2D.quadVertexPtr->Position = { pos.x + 0.5f * size.x, pos.y - 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top right
		s_Data2D.quadVertexPtr->Position = { pos.x + 0.5f * size.x, pos.y + 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top left
		s_Data2D.quadVertexPtr->Position = { pos.x - 0.5f * size.x, pos.y + 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//increase the quad index count
		s_Data2D.quadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const sptr<SubTexture2D>& subtexture, const TextureProps& props)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, subtexture, props);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const sptr<SubTexture2D>& subtexture, const TextureProps& props)
	{
		CheckShouldFlush();

		float textureIndex = 0.0f;

		//check if the texture is already in the draw call and grab it's index if it doesn't
		for (uint32_t i = 1; i < s_Data2D.textureSlotIndex; i++) {
			if (*s_Data2D.textureSlots[i].get() == *subtexture->GetTexture().get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if it is not add it and give it a new index
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data2D.textureSlotIndex;
			s_Data2D.textureSlots[s_Data2D.textureSlotIndex] = subtexture->GetTexture();
			s_Data2D.textureSlotIndex++;
		}

		//bottom left
		s_Data2D.quadVertexPtr->Position = { pos.x - 0.5f * size.x, pos.y - 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[0];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//bottom right
		s_Data2D.quadVertexPtr->Position = { pos.x + 0.5f * size.x, pos.y - 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[1];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top right
		s_Data2D.quadVertexPtr->Position = { pos.x + 0.5f * size.x, pos.y + 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[2];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top left
		s_Data2D.quadVertexPtr->Position = { pos.x - 0.5f * size.x, pos.y + 0.5f * size.y, 0.0f };
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[4];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//increase the quad index count
		s_Data2D.quadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(pos.x, pos.y, 0.0f), size, rotDegrees, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const glm::vec4& color)
	{
		CheckShouldFlush();

		const float texIndex = 0.0f; //all white texture
		const float tilingFactor = 1.0f;

		glm::mat4 trans = glm::translate(pos) *
			glm::toMat4(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rotDegrees)))) *
			glm::scale(glm::vec3(size.x, size.y, 1.0f));

		//bottom left
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[0]);
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//bottom right
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[1]);
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top right
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[2]);
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top left
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[3]);
		s_Data2D.quadVertexPtr->Color = color;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = texIndex;
		s_Data2D.quadVertexPtr->TilingFactor = tilingFactor;
		s_Data2D.quadVertexPtr++;

		//increase the quad index count
		s_Data2D.quadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		DrawRotatedQuad(glm::vec3(pos.x, pos.y, 0.0f), size, rotDegrees, texture, props);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const sptr<Texture2D>& texture, const TextureProps& props)
	{
		CheckShouldFlush();

		float textureIndex = 0.0f;

		//check if the texture is already in the draw call and grab it's index if it doesn't
		for (uint32_t i = 1; i < s_Data2D.textureSlotIndex; i++) {
			if (*s_Data2D.textureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if it is not add it and give it a new index
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data2D.textureSlotIndex;
			s_Data2D.textureSlots[s_Data2D.textureSlotIndex] = texture;
			s_Data2D.textureSlotIndex++;
		}

		glm::mat4 trans = glm::translate(pos) *
			glm::toMat4(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rotDegrees)))) *
			glm::scale(glm::vec3(size.x, size.y, 1.0f));

		//bottom left
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[0]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//bottom right
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[1]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 0.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top right
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[2]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 1.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top left
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[3]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = { 0.0f, 1.0f };
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//increase the quad index count
		s_Data2D.quadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, const float& rotDegrees, const sptr<SubTexture2D>& subtexture, const TextureProps& props)
	{
		DrawRotatedQuad(glm::vec3(pos.x, pos.y, 0.0f), size, rotDegrees, subtexture, props);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, const float& rotDegrees, const sptr<SubTexture2D>& subtexture, const TextureProps& props)
	{
		CheckShouldFlush();

		float textureIndex = 0.0f;

		//check if the texture is already in the draw call and grab it's index if it doesn't
		for (uint32_t i = 1; i < s_Data2D.textureSlotIndex; i++) {
			if (*s_Data2D.textureSlots[i].get() == *subtexture->GetTexture().get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if it is not add it and give it a new index
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data2D.textureSlotIndex;
			s_Data2D.textureSlots[s_Data2D.textureSlotIndex] = subtexture->GetTexture();
			s_Data2D.textureSlotIndex++;
		}

		glm::mat4 trans = glm::translate(pos) *
			glm::toMat4(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rotDegrees)))) *
			glm::scale(glm::vec3(size.x, size.y, 1.0f));

		//bottom left
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[0]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[0];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//bottom right
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[1]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[1];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top right
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[2]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[2];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//top left
		s_Data2D.quadVertexPtr->Position = glm::vec3(trans * s_Data2D.rotatedQuadVertexPositions[3]);
		s_Data2D.quadVertexPtr->Color = props.tint;
		s_Data2D.quadVertexPtr->Uv = subtexture->GetUVs()[3];
		s_Data2D.quadVertexPtr->TexIndex = textureIndex;
		s_Data2D.quadVertexPtr->TilingFactor = props.tilingFactor;
		s_Data2D.quadVertexPtr++;

		//increase the quad index count
		s_Data2D.quadIndexCount += 6;
	}
}