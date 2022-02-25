#pragma once

#include <string>

namespace Graphics
{
	class ShaderProgram
	{
	private:
		unsigned id = 0;

		static std::string ReadShaderFile(const std::string& shaderPath);
		static bool CompileShader(unsigned shaderId, const std::string& code, std::string& errorMessage);
		bool LinkProgram(unsigned vertexShaderId, unsigned fragmentShaderId, std::string& errorMessage);

		static void DeleteShaders(unsigned vertexShaderId, unsigned fragmentShaderId);

		void Delete() const;

		[[nodiscard]] int GetUniformLocation(const std::string& name) const;
	public:
		ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		ShaderProgram(const ShaderProgram& other) = delete;
		ShaderProgram& operator=(const ShaderProgram& other) = delete;
		ShaderProgram(ShaderProgram&& other) noexcept;
		ShaderProgram& operator=(ShaderProgram&& other) noexcept;
		~ShaderProgram();

		void Use() const;
		void UnUse();

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec3f(const std::string& name, float x, float y, float z) const;
		void SetVec4f(const std::string& name, float x, float y, float z, float w) const;
	};
}
