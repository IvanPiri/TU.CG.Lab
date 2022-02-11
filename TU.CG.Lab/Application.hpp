#pragma once

#include <memory>

#include "Utils/Window.hpp"

class Application
{
private:
	std::unique_ptr<Utils::Window> window;

	void Initialize();
	void LoadContent();
	void Update(float deltaTime);
	void Render();
public:
	Application();

	void Run();
};
