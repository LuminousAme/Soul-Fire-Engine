//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Application.cpp - source file for the class that represnets a Soul Fire Application

//precompile header
#include "SF_PCH.h"

#include "Application.h"

//include logging
#include "Logger.h"

#include "Input.h"
#include <glad/glad.h>

#include "SoulFire/Platforms/OpenGL/OpenGLShader.h"

namespace SoulFire {

	Application* Application::s_Instance = nullptr; 

	Application::Application()
	{
		//save the singleton
		s_Instance = this;

		//create a new window
		m_window = std::unique_ptr<Window>(Window::CreateNewWindow());
		//sets the callback so that when the window sends an event, the OnEvent function is called
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_imguiLayer = new ImGuiLayer();
		PushOverlay(m_imguiLayer);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		float vertices[9] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VBO->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IBO.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_IBO->Bind();

		std::string vertShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec3 outPosition;

			void main() {
				outPosition = inPosition;
				gl_Position = vec4(inPosition, 1.0);
			}

		)";

		std::string fragShaderSrc = R"(
			#version 420
			
			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec4 outColor;

			void main() {
				outColor = vec4(inPosition * 0.5 + 0.5, 1.0);
				//outColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

		)";

		m_Shader.reset(Shader::Create());

		m_Shader->LoadShaderStage(vertShaderSrc.c_str(), ShaderType::VERTEX);
		m_Shader->LoadShaderStage(fragShaderSrc.c_str(), ShaderType::FRAGMENT);
		m_Shader->Link();
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& ev) {
		//make a dispatcher
		EventDispatcher dispatcher(ev);
		//check if it's a window close event and if it is, run the window close function
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		//send the events through the layers in reverse order until one of them handles the event
		for (auto it = m_layerTree.end(); it != m_layerTree.begin();) {
			//dispatch the event
			(*--it)->OnEvent(ev);
			//if it is handled after being dispatched stop handing it off
			if (ev.GetHandled()) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerTree.PushLayer(layer);
		layer->Attach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerTree.PushOverlay(overlay);
		overlay->Attach();
	}

	void Application::Run()
	{
		//while the application is running
		while (m_running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			m_Shader->UnBind();

			//update all of the layers
			for (Layer* layer : m_layerTree) layer->Update();

			//begin imgui
			m_imguiLayer->Begin();

			//render imgui for each layer
			for (Layer* layer : m_layerTree) layer->ImGuiRender();

			//end imgui 
			m_imguiLayer->End();

			//update the window
			m_window->Update();

			//reset the keys at the end of the frame
			Input::ResetInput();
		}
	}


	//when the window close event is dispatched
	bool Application::OnWindowClose(WindowCloseEvent& ev)
	{
		//set the application running to false
		m_running = false;
		//and the event handled is true
		return true;
	}
}