//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Shader.cpp - source file for the class that represnets a complete shader program that can interface with different API 
#include "SF_PCH.h"
#include "Shader.h"

#include "SoulFire/Platforms/OpenGL/OpenGLShader.h"

namespace SoulFire {
	Shader* Shader::Create(const std::string& name)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::NONE:
			SF_ENGINE_LOG_ERROR("No graphics API selected");
			return nullptr;
		case RendererAPI::API::OPENGL:
			return new OpenGLShader(name);
		}

		SF_ENGINE_LOG_ERROR("Unknown Graphics API");

		return nullptr;
	}
	void ShaderLibrary::Add(const sptr<Shader>& shader)
	{
		std::string name = shader->GetName();
		SF_ENGINE_LOG_ASSERT(!Exists(name), "Shader already exists!");
		m_shaders[name] = shader;
	}

	sptr<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		auto lastDot = filePath.rfind('.');

		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

		std::string name = filePath.substr(lastSlash, count);

		return Load(name, filePath);
	}

	sptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		sptr<Shader> newShader;
		newShader.reset(Shader::Create(name));
		newShader->LoadFullShaderFromFile(filePath.c_str());
		newShader->Link();

		Add(newShader);

		return newShader;
	}

	sptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		sptr<Shader> newShader;
		newShader.reset(Shader::Create(name));
		newShader->LoadShaderStageFromFile(vertexFilePath.c_str(), ShaderType::VERTEX);
		newShader->LoadShaderStageFromFile(fragmentFilePath.c_str(), ShaderType::FRAGMENT);
		newShader->Link();

		Add(newShader);

		return newShader;
	}

	sptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name)) {
			SF_ENGINE_LOG_ERROR("Shader Not Found!");
			return nullptr;
		}
		return m_shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}
}