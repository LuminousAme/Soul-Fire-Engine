#pragma once
#include <SoulFire.h>
#include <Imgui/imgui.h>

//using namespace SoulFire::RendererEnums;

class TestLayer : public SoulFire::Layer {
public:
	TestLayer()
		: Layer("App Test")
	{
		lastPos = glm::vec2(SoulFire::Input::GetMouseX(), SoulFire::Input::GetMouseY());

		m_Camera = SoulFire::Camera::Create(2.0 * -1.6f, 2.0 * 1.6f, 2.0 * -1.0f, 2.0 * 1.0f, -1.0f, 1.0f);
		m_Camera->SetPosition(glm::vec3(0.5f, 0.5f, 0.0f));

		m_TriangleTrans = SoulFire::Transform();
		m_SquareTrans = SoulFire::Transform();

		m_VAO = SoulFire::VertexArrayObject::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		SoulFire::sptr<SoulFire::VertexBuffer> VBO;
		VBO = SoulFire::VertexBuffer::Create(vertices, sizeof(vertices));

		//create the layout
		SoulFire::BufferLayout layout = {
			{SoulFire::ShaderDataType::Vec3, "inPosition"},
			{SoulFire::ShaderDataType::Vec4, "inColor"}
		};
		VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(VBO);

		uint32_t indices[3] = { 0, 1, 2 };
		SoulFire::sptr<SoulFire::IndexBuffer> IBO;
		IBO = SoulFire::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VAO->SetIndexBuffer(IBO);

		m_SquareVAO = SoulFire::VertexArrayObject::Create();

		float squareVertices[4 * 5] = {
			-0.75f,	 -0.75f,  0.0f,  0.0f,  0.0f,
			0.75f,   -0.75f,  0.0f,  1.0f,  0.0f,
			0.75f,    0.75f,  0.0f,  1.0f,  1.0f,
			-0.75f,   0.75f,  0.0f,  0.0f,  1.0f
		};
		SoulFire::sptr<SoulFire::VertexBuffer> sqaureVBO;
		sqaureVBO = SoulFire::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		sqaureVBO->SetLayout({ 
			{ SoulFire::ShaderDataType::Vec3, "inPosition" },
			{ SoulFire::ShaderDataType::Vec2, "inUv" }
			});
		m_SquareVAO->AddVertexBuffer(sqaureVBO);

		uint32_t sqaureIndices[6] = { 0, 1, 2, 2, 3, 0 };
		SoulFire::sptr<SoulFire::IndexBuffer> sqaureIBO;
		sqaureIBO = SoulFire::IndexBuffer::Create(sqaureIndices, sizeof(sqaureIndices) / sizeof(uint32_t));
		m_SquareVAO->SetIndexBuffer(sqaureIBO);

		std::string vertShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;
			layout(location = 0) out vec3 outPosition;
			layout(location = 1) out vec4 outColor;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			void main() {
				outPosition = inPosition;
				outColor = inColor;
				gl_Position = u_ViewProjection * u_Model * vec4(inPosition, 1.0);
			}

		)";

		std::string fragShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;
			layout(location = 0) out vec4 outColor;

			uniform vec4 u_Color;

			void main() {
				outColor = u_Color;
				//outColor =  inColor;
				//outColor = vec4(inPosition * 0.5 + 0.5, 1.0);
				//outColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

		)";

		std::string squareVertShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec3 outPosition;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			void main() {
				outPosition = inPosition;
				gl_Position = u_ViewProjection * u_Model * vec4(inPosition, 1.0);
			}

		)";

		std::string sqaureFragShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec4 outColor;

			uniform vec4 u_Color;

			void main() {
				outColor = u_Color;
				//outColor = vec4(inPosition * 0.5 + 0.5, 1.0);
				//outColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

		)";

		m_Shader = SoulFire::Shader::Create("TriangleShader");

		m_Shader->LoadShaderStage(vertShaderSrc.c_str(), SoulFire::ShaderType::VERTEX);
		m_Shader->LoadShaderStage(fragShaderSrc.c_str(), SoulFire::ShaderType::FRAGMENT);
		m_Shader->Link();

		m_SquareShader = SoulFire::Shader::Create("SquareShader");

		m_SquareShader->LoadShaderStage(squareVertShaderSrc.c_str(), SoulFire::ShaderType::VERTEX);
		m_SquareShader->LoadShaderStage(sqaureFragShaderSrc.c_str(), SoulFire::ShaderType::FRAGMENT);
		m_SquareShader->Link();

		std::string textureVertShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec2 inUv;
			layout(location = 0) out vec3 outPosition;
			layout(location = 1) out vec2 outUv;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			void main() {
				outUv = inUv;
				outPosition = inPosition;
				gl_Position = u_ViewProjection * u_Model * vec4(inPosition, 1.0);
			}

		)";

		std::string textureFragShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec2 inUv;
			layout(location = 0) out vec4 outColor;
			
			layout(binding = 0) uniform sampler2D s_Texture;

			void main() {
				outColor = texture(s_Texture, inUv);
				//outColor = vec4(inUv, 0.0, 1.0);
				//outColor = vec4(inPosition * 0.5 + 0.5, 1.0);
				//outColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

		)";

		m_shaderLibrary.Load("assets/shaders/texture.glsl");

		m_texture = SoulFire::Texture2D::Create("assets/textures/necoarcpink.png");
		m_textureTransparent = SoulFire::Texture2D::Create("assets/textures/necoarctransparent.png");
	}

	void Update() override {
		//Objects
		glm::vec3 move = glm::vec3(0.0f);
		if (SoulFire::Input::GetKey(SF_KEY_D) || SoulFire::Input::GetKey(SF_KEY_RIGHT)) move.x += objectMoveSpeed;
		else if (SoulFire::Input::GetKey(SF_KEY_A) || SoulFire::Input::GetKey(SF_KEY_LEFT)) move.x -= objectMoveSpeed;
		if (SoulFire::Input::GetKey(SF_KEY_W) || SoulFire::Input::GetKey(SF_KEY_UP)) move.y += objectMoveSpeed;
		else if (SoulFire::Input::GetKey(SF_KEY_S) || SoulFire::Input::GetKey(SF_KEY_DOWN)) move.y -= objectMoveSpeed;
		if (SoulFire::Input::GetKey(SF_KEY_Q)) move.z += objectMoveSpeed;
		else if (SoulFire::Input::GetKey(SF_KEY_E)) move.z -= objectMoveSpeed;

		if (glm::length(move) > 0.0f) {
			move = glm::normalize(move);
			move *= SoulFire::Time::GetDeltaTime();
			m_SquareTrans.SetPosition(m_SquareTrans.GetPosition() + move);
		}

		if (SoulFire::Input::GetKeyDown(SF_KEY_TAB)) {
			glm::vec2 currentPos = glm::vec2(SoulFire::Input::GetMouseX(), SoulFire::Input::GetMouseY());

			float dist = glm::distance(currentPos, lastPos);
			SF_LOG_TRACE("Current position: {0}, {1}! Last Position: {2}, {3}!", currentPos.x, currentPos.y, lastPos.x, lastPos.y);
			SF_LOG_TRACE("The mouse has moved {0} pixels!", dist);

			lastPos = currentPos;
		}

		int clearFlags = (SoulFire::ClearFlags::ClearColorBuffer | SoulFire::ClearFlags::ClearDepthBuffer);
		SoulFire::RenderCommand::Clear(clearFlags, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

		SoulFire::Renderer::BeginRenderPass(m_Camera);

		m_SquareShader->Bind();
		m_SquareShader->SetUniform("u_Color", m_objectColour);
		m_SquareShader->UnBind();

		m_Shader->Bind();
		m_Shader->SetUniform("u_Color", m_objectColour);
		m_Shader->UnBind();

		m_textureTransparent->Bind(0);
		//m_texturedShader->SetUniform("u_Texture", 0);

		SoulFire::Renderer::AddToPass(m_VAO, m_Shader, m_TriangleTrans);
		SoulFire::Renderer::AddToPass(m_SquareVAO, m_shaderLibrary.Get("texture"), m_SquareTrans);

		m_texture->UnBind(0);
		SoulFire::Renderer::EndRenderPass();
	}

	void OnEvent(SoulFire::Event& ev) override {
	}

	void ImGuiRender() override {
		ImGui::Begin("Test Layer Box");

		ImGui::Text("Hello world!");

		ImGui::ColorPicker4("Object Colour", glm::value_ptr(m_objectColour));

		ImGui::End();
	}

private:
	glm::vec2 lastPos = glm::vec2(0.0f, 0.0f);

	SoulFire::ShaderLibrary m_shaderLibrary;

	SoulFire::sptr<SoulFire::Shader> m_Shader;
	SoulFire::sptr<SoulFire::VertexArrayObject> m_VAO;

	SoulFire::sptr<SoulFire::Shader> m_SquareShader;
	SoulFire::sptr<SoulFire::VertexArrayObject> m_SquareVAO;
	SoulFire::sptr<SoulFire::Camera> m_Camera;

	float camMoveSpeed = 2.5f;
	float camRotSpeed = 90.0f;

	SoulFire::Transform m_SquareTrans;
	SoulFire::Transform m_TriangleTrans;
	float objectMoveSpeed = 5.0f;

	glm::vec4 m_objectColour = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);

	SoulFire::sptr<SoulFire::Texture2D> m_texture;
	SoulFire::sptr<SoulFire::Texture2D> m_textureTransparent;
};