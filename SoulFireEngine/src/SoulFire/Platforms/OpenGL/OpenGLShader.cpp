//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OpenGLShader.cpp - source file for the class that represnets a complete shader program for the OpenGL 3 API

#include "SF_PCH.h"
#include "OpenGLShader.h"

namespace SoulFire {
	static ShaderType ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return ShaderType::VERTEX;
		else if (type == "fragment") return ShaderType::FRAGMENT;
		else return ShaderType::None;
	}

	OpenGLShader::OpenGLShader(const std::string& name)
		: m_vs(0), m_fs(0), m_handle(0), m_name(name)
	{
		m_handle = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		//if the program exists within opengl
		if (m_handle != 0) {
			//then delete it and set the handle to 0 again
			glDeleteProgram(m_handle);
			m_handle = 0;
		}
	}

	bool OpenGLShader::LoadShaderStage(const char* sourceCode, ShaderType shaderType)
	{
		//if it's a valid shader stage return false
		if (shaderType == ShaderType::None) return false;

		//create a new shader stage
		GLuint handle = glCreateShader(ConvertShaderType(shaderType));

		//Load and compile the GLSL sourcecode
		glShaderSource(handle, 1, &sourceCode, nullptr);
		glCompileShader(handle);

		//Get the compilation status of the shader stage (so we can check if it compiled properly)
		GLint status = 0;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

		//check if it compiled properly 
		if (status == GL_FALSE) {
			//if it did not, log an error

			//get the size of the log (so we can use OpenGL's error log)
			GLint logSize = 0;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);

			//create a new character array buffer for the log to store in
			char* log = new char[logSize];

			//get the log
			glGetShaderInfoLog(handle, logSize, &logSize, log);

			//log the errror in our own system
			SF_ENGINE_LOG_ERROR("Failed to compile shader stage: {0}", log);

			//clean up the memory of the log
			delete[] log;

			//Delete the broken shader stage so it doesn't waste memory
			glDeleteShader(handle);
			handle = 0;
		}

		//save the handle so it can be accessed later 
		switch (shaderType) {
		case SoulFire::ShaderType::VERTEX:
			m_vs = handle;
			break;
		case SoulFire::ShaderType::FRAGMENT:
			m_fs = handle;
			break;
		default:
			SF_ENGINE_LOG_WARNING("Shader type not implemented");
			break;
		}

		return status != GL_FALSE;
	}

	bool OpenGLShader::LoadShaderStageFromFile(const char* filePath, ShaderType shaderType)
	{
		//open the file 
		std::ifstream file(filePath);

		if (!file.is_open()) {
			//if it did fail to open log an error
			SF_ENGINE_LOG_ERROR("Shader file not found: {0}", filePath);
			//and throw a runtime error
			throw std::runtime_error("File not found, see logs");
		}

		//if it did open correctly then make a stream to parse it
		std::stringstream stream;
		//begin parsing it
		stream << file.rdbuf();
		//use the load function earlier to load the shader from the stream and save if it was sucessful in a boolean
		bool result = LoadShaderStage(stream.str().c_str(), shaderType);
		//close the file
		file.close();

		return result;
	}

	bool OpenGLShader::LoadFullShaderFromFile(const char* filePath)
	{
		//open the file 
		std::ifstream file(filePath);

		if (!file.is_open()) {
			//if it did fail to open log an error
			SF_ENGINE_LOG_ERROR("Shader file not found: {0}", filePath);
			//and throw a runtime error
			throw std::runtime_error("File not found, see logs");
		}

		//if it did open correctly then make a stream to parse it
		std::stringstream stream;
		//begin parsing it
		stream << file.rdbuf();
		std::string raw = stream.str();

		auto allShaderSources = PreProcess(raw);

		bool result = false;
		for (auto& entry : allShaderSources) {
			result = LoadShaderStage(entry.second.c_str(), entry.first);
			if (!result) break;
		}

		return result;
	}

	bool OpenGLShader::Link()
	{
		if (m_vs == 0 || m_fs == 0) {
			SF_ENGINE_LOG_ERROR("Both a vertex and fragment shader need to be attached to compile a shader program.");
			return false;
		}

		//Attach our shaders
		glAttachShader(m_handle, m_vs);
		glAttachShader(m_handle, m_fs);

		//Perform linking
		glLinkProgram(m_handle);

		//Remove shader stages to save memory
		glDetachShader(m_handle, m_vs);
		glDeleteShader(m_vs);
		glDetachShader(m_handle, m_fs);
		glDeleteShader(m_fs);

		//Setup a check to make sure the shader program compiled and linked correclty
		GLint status = 0;
		glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
		
		//check if it failed to compile or link
		if (status == GL_FALSE)
		{
			//if it did not, create an error log

			GLint lenght = 0;
			glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &lenght);

			//if openGL has made an error log
			if (lenght > 0) {
				//read it's log
				char* log = new char[lenght];
				glGetProgramInfoLog(m_handle, lenght, &lenght, log);
				//log the error
				SF_ENGINE_LOG_ERROR("Shader failed to link: {0}", log);
				delete[] log;
			}
			else {
				//if opengl did not generate an error log, just say the error is unknown in the log
				SF_ENGINE_LOG_ERROR("Shader failed to link: error unknown");
			}
		}

		return status != GL_FALSE;
	}


	GLenum OpenGLShader::ConvertShaderType(ShaderType type)
	{
		switch (type)
		{
		case SoulFire::ShaderType::VERTEX:
			return GL_VERTEX_SHADER;
		case SoulFire::ShaderType::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		default:
			return GL_NONE;
		}
	}

	void OpenGLShader::SetUniform(const std::string& name, const float& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform1fv(m_handle, location, count, &value);
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::vec2& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform2fv(m_handle, location, count, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::vec3& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform3fv(m_handle, location, count, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::vec4& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform4fv(m_handle, location, count, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const int& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform1iv(m_handle, location, count, &value);
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::ivec2& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform2iv(m_handle, location, count, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::ivec3& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform3iv(m_handle, location, count, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::ivec4& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform4iv(m_handle, location, count, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniform(const std::string& name, const bool& value, int count)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniform1i(location, value, 1);
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniformMatrix(const std::string& name, const glm::mat3& value, int count, bool transposed)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniformMatrix3fv(m_handle, location, count, transposed, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	void OpenGLShader::SetUniformMatrix(const std::string& name, const glm::mat4& value, int count, bool transposed)
	{
		int location = GetUniformLocation(name);
		if (location != -1) {
			glProgramUniformMatrix4fv(m_handle, location, count, transposed, glm::value_ptr(value));
		}
		else SF_LOG_WARNING("Could not find uniform {0}!", name);
	}

	std::unordered_map<ShaderType, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<ShaderType, std::string> shaderSourceCodes;

		const char* typeToken = "#type";
		size_t ttlen = strlen(typeToken);
		size_t position = source.find(typeToken, 0);
		while (position != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", position);
			SF_ENGINE_LOG_ASSERT(eol != std::string::npos, "Syntax error in shader code");
			size_t begin = position + ttlen + 1;
			std::string type = source.substr(begin, eol - begin);
			SF_ENGINE_LOG_ASSERT(ShaderTypeFromString(type) != ShaderType::None, "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			position = source.find(typeToken, nextLinePos);
			shaderSourceCodes[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				position - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSourceCodes;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		std::unordered_map<std::string, int>::const_iterator it = m_uniformLocations.find(name);
		int result = -1;

		//if we haven't store the location yet grab it from opengl
		if (it == m_uniformLocations.end()) {
			result = glGetUniformLocation(m_handle, name.c_str());
			m_uniformLocations[name] = result;
		}
		//other we have already saved it, so just return it
		else {
			result = it->second;
		}

		return result;
	}
}