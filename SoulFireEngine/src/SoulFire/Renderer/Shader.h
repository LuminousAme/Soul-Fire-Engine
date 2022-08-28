//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Shader.h - header file for the class that represnets a complete shader program that can interface with different API 
#pragma once

#include "Renderer.h"

namespace SoulFire {
	enum class ShaderType
	{
		None = 0,
		VERTEX,
		FRAGMENT
	};

	class Shader {
	public:
		typedef std::shared_ptr<Shader> sptr;
	public:
		virtual ~Shader() {};

		//loads a single stage of the shader (vertex, fragment, etc.) and returns if sucessful
		virtual bool LoadShaderStage(const char* sourceCode, ShaderType shaderType) = 0;

		//loads a single stage of the shader from an external files and returns if sucessful
		virtual bool LoadShaderStageFromFile(const char* filePath, ShaderType shaderType) = 0;

		//Links the stages together creating the full shader pipeline and making it useable, returns if sucessful
		virtual bool Link() = 0;

		//Binds the shader program so we can acutally use it
		virtual void Bind() const = 0;

		//Unbinds the shader program so we can use another
		virtual void UnBind() const = 0;

		//creates a shader
		static Shader* Create();
	};
}