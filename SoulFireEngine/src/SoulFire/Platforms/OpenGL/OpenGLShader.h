//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLShader.h - header file for the class that represnets a complete shader program for the OpenGL 3 API
#pragma once

#include "SoulFire/Renderer/Shader.h"
#include "glad/glad.h"

namespace SoulFire {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader();
		~OpenGLShader();

		//loads a single stage of the shader (vertex, fragment, etc.) and returns if sucessful
		bool LoadShaderStage(const char* sourceCode, ShaderType shaderType) override;

		//loads a single stage of the shader from an external files and returns if sucessful
		bool LoadShaderStageFromFile(const char* filePath, ShaderType shaderType) override;

		//Links the stages together creating the full shader pipeline and making it useable, returns if sucessful
		bool Link() override;

		//Binds the shader program so we can acutally use it
		void Bind() override;

		//Unbinds the shader program so we can use another
		void UnBind() override;

	private:
		//vertex shader
		GLuint m_vs;
		//fragment shader
		GLuint m_fs;
		//handle for the shader program
		GLuint m_handle;

		GLenum ConvertShaderType(ShaderType type);
	};
}