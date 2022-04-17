#include "ShaderProgram.hpp"

#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Graphics
{
	ShaderProgram::ShaderProgram(
		const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		const std::string vertexShaderCode = ReadShaderFile(vertexShaderPath);
		const std::string fragmentShaderCode = ReadShaderFile(fragmentShaderPath);

		const unsigned vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		const unsigned fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		std::string errorMessage;

		if (!CompileShader(vertexShaderId, vertexShaderCode, errorMessage))
		{
			DeleteShaders(vertexShaderId, fragmentShaderId);

			throw std::exception(errorMessage.c_str());
		}

		if (!CompileShader(fragmentShaderId, fragmentShaderCode, errorMessage))
		{
			DeleteShaders(vertexShaderId, fragmentShaderId);

			throw std::exception(errorMessage.c_str());
		}

		if (!LinkProgram(vertexShaderId, fragmentShaderId, errorMessage))
		{
			glDetachShader(id, vertexShaderId);
			glDetachShader(id, fragmentShaderId);

			DeleteShaders(vertexShaderId, fragmentShaderId);
			Delete();

			throw std::exception(errorMessage.c_str());
		}

		glDetachShader(id, vertexShaderId);
		glDetachShader(id, fragmentShaderId);

		DeleteShaders(vertexShaderId, fragmentShaderId);
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
		: id(other.id)
	{
		other.id = 0;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			other.id = 0;
		}

		return *this;
	}

	ShaderProgram::~ShaderProgram()
	{
		Delete();
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(id);
	}

	void ShaderProgram::UnUse()
	{
		glUseProgram(0);
	}

	void ShaderProgram::SetBool(const std::string& name, const bool value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniform1i(uniformLocation, value);
	}

	void ShaderProgram::SetInt(const std::string& name, const int value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniform1i(uniformLocation, value);
	}

	void ShaderProgram::SetFloat(const std::string& name, const float value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniform1f(uniformLocation, value);
	}

	void ShaderProgram::SetVec2f(const std::string& name, const glm::vec2 value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniform2f(uniformLocation, value.x, value.y);
	}

	void ShaderProgram::SetVec3f(const std::string& name, const glm::vec3 value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void ShaderProgram::SetVec4f(const std::string& name, const glm::vec4 value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::SetMat3f(const std::string& name, const glm::mat3 value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::SetMat4f(const std::string& name, const glm::mat4 value) const
	{
		const int uniformLocation = GetUniformLocation(name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	std::string ShaderProgram::ReadShaderFile(const std::string& shaderPath)
	{
		std::ifstream shaderFile;
		std::stringstream shaderStream;

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		shaderFile.open(shaderPath);

		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		return shaderStream.str();
	}

	bool ShaderProgram::CompileShader(
		const unsigned shaderId, const std::string& code, std::string& errorMessage)
	{
		const char* codeCString = code.c_str();

		glShaderSource(shaderId, 1, &codeCString, nullptr);
		glCompileShader(shaderId);

		int status;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			char infoLog[512];
			glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);

			errorMessage = "Could not compile shader:\r\n";
			errorMessage.append(infoLog);

			return false;
		}

		return true;
	}

	bool ShaderProgram::LinkProgram(
		const unsigned vertexShaderId, const unsigned fragmentShaderId, std::string& errorMessage)
	{
		id = glCreateProgram();

		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragmentShaderId);
		glLinkProgram(id);

		int status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);

		if (status != GL_TRUE)
		{
			char infoLog[512];
			glGetProgramInfoLog(id, 512, nullptr, infoLog);

			errorMessage = "Could not link Shader program:\r\n";
			errorMessage.append(infoLog);

			return false;
		}

		return true;
	}

	void ShaderProgram::DeleteShaders(
		const unsigned vertexShaderId, const unsigned fragmentShaderId)
	{
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	void ShaderProgram::Delete() const
	{
		glDeleteProgram(id);
	}

	int ShaderProgram::GetUniformLocation(const std::string& name) const
	{
		const int uniformLocation = glGetUniformLocation(id, name.c_str());

		if (uniformLocation == -1)
		{
			const std::string errorMessage = "Uniform { " + name +
				" } could not be found in the shader code. Is it unused?";

			throw std::exception(errorMessage.c_str());
		}

		return uniformLocation;
	}
}
