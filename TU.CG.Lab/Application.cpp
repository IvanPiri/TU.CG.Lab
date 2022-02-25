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
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top
	};

	va = std::make_unique<Graphics::VertexArray>();
	auto vb = std::make_unique<Graphics::VertexBuffer>(vertices, sizeof vertices);

	vb->SetAttributes({
		{"aPos", Graphics::VertexAttributeType::VEC3F},
		{"aColor", Graphics::VertexAttributeType::VEC3F},
	});

	va->SetVertexBuffer(std::move(vb));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	va->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	va->Unbind();
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
}
