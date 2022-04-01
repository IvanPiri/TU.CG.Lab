#pragma once

#include <memory>

#include "IApplication.hpp"
#include "../Graphics/ShaderProgram.hpp"
#include "../Graphics/VertexArray.hpp"
#include "../Input/InputManager.hpp"
#include "../Utils/Camera.hpp"
#include "../Utils/ContentManager.hpp"
#include "../Utils/Window.hpp"

namespace Applications
{
	class Application_Lighting : public IApplication
	{
	private:
		Input::InputManager inputManager;
		Utils::ContentManager content;

		std::unique_ptr<Utils::Camera> camera;
		std::unique_ptr<Utils::Window> window;
		std::unique_ptr<Graphics::ShaderProgram> shaderProgram;
		std::unique_ptr<Graphics::ShaderProgram> lightShaderProgram;
		std::unique_ptr<Graphics::VertexArray> va;
		std::unique_ptr<Graphics::VertexArray> lightVa;

		glm::vec3 lightPos;

		void Initialize();
		void LoadContent();
		void UnloadContent();
		void Update(float deltaTime);
		void Render() const;
	public:
		Application_Lighting();

		void Run();

		Input::InputManager& GetInputManager() override { return inputManager; }
	};
}
