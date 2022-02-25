#pragma once

#include <memory>

#include "Graphics/ShaderProgram.hpp"
#include "Graphics/VertexArray.hpp"
#include "Input/InputManager.hpp"
#include "Utils/Window.hpp"

class Application
{
private:
	Input::InputManager inputManager;
	std::unique_ptr<Utils::Window> window;
	std::unique_ptr<Graphics::ShaderProgram> shaderProgram;
	std::unique_ptr<Graphics::VertexArray> va;

	void Initialize();
	void LoadContent();
	void Update(float deltaTime);
	void Render() const;
public:
	Application();

	void Run();

	Input::InputManager& GetInputManager() { return inputManager; }
};
