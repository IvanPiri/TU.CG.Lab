#include "Application.hpp"

#include <glad/glad.h>

Application::Application()
{
	window = std::make_unique<Utils::Window>("TU.CG.Lab", 800, 600);
}

void Application::Initialize()
{
	window->ActivateInputFor(this);
}

void Application::LoadContent()
{
}

void Application::Update(const float deltaTime)
{
}

void Application::Render()
{
	glClearColor(0.393f, 0.585f, 0.930f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::Run()
{
	Initialize();
	LoadContent();

	float lastFrame = 0.0f;

	while (!window->GetShouldClose())
	{
		const float currentFrame = window->GetElapsedTime();
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Update(deltaTime);
		Render();

		window->SwapBuffers();
		window->PollEvents();
	}
}
