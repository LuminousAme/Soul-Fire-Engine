#pragma once
#include <SoulFire.h>
#include <Imgui/imgui.h>

class TestLayer : public SoulFire::Layer {
public:
	TestLayer()
		: Layer("App Test")
	{
		lastPos = glm::vec2(SoulFire::Input::GetMouseX(), SoulFire::Input::GetMouseY());

		m_VAO.reset(SoulFire::VertexArrayObject::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		SoulFire::VertexBuffer::sptr VBO;
		VBO.reset(SoulFire::VertexBuffer::Create(vertices, sizeof(vertices)));

		//create the layout
		SoulFire::BufferLayout layout = {
			{SoulFire::ShaderDataType::Vec3, "inPosition"},
			{SoulFire::ShaderDataType::Vec4, "inColor"}
		};
		VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(VBO);

		uint32_t indices[3] = { 0, 1, 2 };
		SoulFire::IndexBuffer::sptr IBO;
		IBO.reset(SoulFire::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VAO->SetIndexBuffer(IBO);

		m_SquareVAO.reset(SoulFire::VertexArrayObject::Create());

		float squareVertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};
		SoulFire::VertexBuffer::sptr sqaureVBO;
		sqaureVBO.reset(SoulFire::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		sqaureVBO->SetLayout({ { SoulFire::ShaderDataType::Vec3, "inPosition" } });
		m_SquareVAO->AddVertexBuffer(sqaureVBO);

		uint32_t sqaureIndices[6] = { 0, 1, 2, 2, 3, 0 };
		SoulFire::IndexBuffer::sptr sqaureIBO;
		sqaureIBO.reset(SoulFire::IndexBuffer::Create(sqaureIndices, sizeof(sqaureIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(sqaureIBO);

		std::string vertShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;
			layout(location = 0) out vec3 outPosition;
			layout(location = 1) out vec4 outColor;

			void main() {
				outPosition = inPosition;
				outColor = inColor;
				gl_Position = vec4(inPosition, 1.0);
			}

		)";

		std::string fragShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;
			layout(location = 0) out vec4 outColor;

			void main() {
				outColor =  inColor;
				//outColor = vec4(inPosition * 0.5 + 0.5, 1.0);
				//outColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

		)";

		std::string squareVertShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec3 outPosition;

			void main() {
				outPosition = inPosition;
				gl_Position = vec4(inPosition, 1.0);
			}

		)";

		std::string sqaureFragShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec4 outColor;

			void main() {
				outColor = vec4(inPosition * 0.5 + 0.5, 1.0);
				//outColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

		)";

		m_Shader.reset(SoulFire::Shader::Create());

		m_Shader->LoadShaderStage(vertShaderSrc.c_str(), SoulFire::ShaderType::VERTEX);
		m_Shader->LoadShaderStage(fragShaderSrc.c_str(), SoulFire::ShaderType::FRAGMENT);
		m_Shader->Link();

		m_SquareShader.reset(SoulFire::Shader::Create());

		m_SquareShader->LoadShaderStage(squareVertShaderSrc.c_str(), SoulFire::ShaderType::VERTEX);
		m_SquareShader->LoadShaderStage(sqaureFragShaderSrc.c_str(), SoulFire::ShaderType::FRAGMENT);
		m_SquareShader->Link();
	}

	void Update() override {
		if (SoulFire::Input::GetKeyDown(SF_KEY_TAB)) {
			glm::vec2 currentPos = glm::vec2(SoulFire::Input::GetMouseX(), SoulFire::Input::GetMouseY());

			float dist = glm::distance(currentPos, lastPos);
			SF_LOG_TRACE("Current position: {0}, {1}! Last Position: {2}, {3}!", currentPos.x, currentPos.y, lastPos.x, lastPos.y);
			SF_LOG_TRACE("The mouse has moved {0} pixels!", dist);

			lastPos = currentPos;
		}

		SoulFire::RenderCommand::Clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

		SoulFire::Renderer::BeginRenderPass();

		m_SquareShader->Bind();
		SoulFire::RenderCommand::Draw(m_SquareVAO);
		m_SquareShader->UnBind();


		m_Shader->Bind();
		SoulFire::RenderCommand::Draw(m_VAO);
		m_Shader->UnBind();

		SoulFire::Renderer::EndRenderPass();
	}

	void ImGuiRender() override {
		ImGui::Begin("Test Layer Box");

		ImGui::Text("Hello world!");

		ImGui::End();
	}

private:
	glm::vec2 lastPos = glm::vec2(0.0f, 0.0f);

	SoulFire::Shader::sptr m_Shader;
	SoulFire::VertexArrayObject::sptr m_VAO;

	SoulFire::Shader::sptr m_SquareShader;
	SoulFire::VertexArrayObject::sptr m_SquareVAO;
};