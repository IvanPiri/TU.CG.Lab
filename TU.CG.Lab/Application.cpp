#include "Application.hpp"

#include <glad/glad.h>

#include "Utils/Constants.hpp"

Application::Application()
{
	window = std::make_unique<Utils::Window>("TU.CG.Lab", 800, 600);
}

void Application::Initialize()
{
	window->ActivateInputFor(this);

	constexpr float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindVertexArray(vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
}

void Application::LoadContent()
{
	const std::string vertexShaderPath = Utils::SHADER_PATH + "getting_started.vert";
	const std::string fragmentShaderPath = Utils::SHADER_PATH + "getting_started.frag";

	shaderProgram = std::make_unique<Graphics::ShaderProgram>(
		vertexShaderPath, fragmentShaderPath);
}

void Application::Update(const float deltaTime)
{
	if (inputManager.IsKeyDown(Input::Keys::ESCAPE))
		window->SetShouldClose(true);

	inputManager.ResetState();
}

void Application::Render() const
{
	glClearColor(0.393f, 0.585f, 0.930f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	shaderProgram->UnUse();
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

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vboId);
}
