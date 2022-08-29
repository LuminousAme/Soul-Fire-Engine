//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Shader.h - header file for the class that represnets a complete shader program that can interface with different API 
#pragma once

#include "RenderCommand.h"

namespace SoulFire {
	enum class ShaderType
	{
		None = 0,
		VERTEX,
		FRAGMENT
	};

	class Shader {
	public:
		virtual ~Shader() {};

		//loads a single stage of the shader (vertex, fragment, etc.) and returns if sucessful
		virtual bool LoadShaderStage(const char* sourceCode, ShaderType shaderType) = 0;

		//loads a single stage of the shader from an external files and returns if sucessful
		virtual bool LoadShaderStageFromFile(const char* filePath, ShaderType shaderType) = 0;

		//loads a full shader from an external file and returns if sucessful
		virtual bool LoadFullShaderFromFile(const char* filePath) = 0;

		//Links the stages together creating the full shader pipeline and making it useable, returns if sucessful
		virtual bool Link() = 0;

		//Binds the shader program so we can acutally use it
		virtual void Bind() const = 0;

		//Unbinds the shader program so we can use another
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;

		//sets a uniform
		virtual void SetUniform(const std::string& name, const float& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const glm::vec2& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const glm::vec3& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const glm::vec4& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const int& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const glm::ivec2& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const glm::ivec3& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const glm::ivec4& value, int count = 1) = 0;
		virtual void SetUniform(const std::string& name, const bool& value, int count = 1) = 0;
		
		virtual void SetUniformMatrix(const std::string& name, const glm::mat3& value, int count = 1, bool transposed = false) = 0;
		virtual void SetUniformMatrix(const std::string& name, const glm::mat4& value, int count = 1, bool transposed = false) = 0;

		//creates a shader
		static Shader* Create(const std::string& name);
	};

	class ShaderLibrary {
	public:
		void Add(const sptr<Shader>& shader);
		sptr<Shader> Load(const std::string& filePath);
		sptr<Shader> Load(const std::string& name, const std::string& filePath);
		sptr<Shader> Load(const std::string& name, const std::string& vertexFilePath, const std::string& fragmentFilePath);

		sptr<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, sptr<Shader>> m_shaders;
	};
}