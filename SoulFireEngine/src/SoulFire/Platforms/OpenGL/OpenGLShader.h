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
		void Bind() const override { glUseProgram(m_handle); }

		//Unbinds the shader program so we can use another
		void UnBind() const override { glUseProgram(0); }

		void SetUniform(const std::string& name, const float& value, int count = 1) override;
		void SetUniform(const std::string& name, const glm::vec2& value, int count = 1) override;
		void SetUniform(const std::string& name, const glm::vec3& value, int count = 1) override;
		void SetUniform(const std::string& name, const glm::vec4& value, int count = 1) override;
		void SetUniform(const std::string& name, const int& value, int count = 1) override;
		void SetUniform(const std::string& name, const glm::ivec2& value, int count = 1) override;
		void SetUniform(const std::string& name, const glm::ivec3& value, int count = 1) override;
		void SetUniform(const std::string& name, const glm::ivec4& value, int count = 1) override;
		void SetUniform(const std::string& name, const bool& value, int count = 1) override;

		void SetUniformMatrix(const std::string& name, const glm::mat3& value, int count = 1, bool transposed = false) override;
		void SetUniformMatrix(const std::string& name, const glm::mat4& value, int count = 1, bool transposed = false) override;

	private:
		//vertex shader
		GLuint m_vs;
		//fragment shader
		GLuint m_fs;
		//handle for the shader program
		GLuint m_handle;

		GLenum ConvertShaderType(ShaderType type);

		//unordered map to store the locations of all the uniforms
		std::unordered_map<std::string, int> m_uniformLocations;
		//function to get the locations of all the uniforms
		int GetUniformLocation(const std::string& name);
	};
}