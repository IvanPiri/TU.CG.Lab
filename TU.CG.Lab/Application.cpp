#include "Application.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f,   // top left
	};

	constexpr unsigned indices[] =
	{
		// note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
	};

	va = std::make_unique<Graphics::VertexArray>();
	auto vb = std::make_unique<Graphics::VertexBuffer>(vertices, sizeof vertices);
	auto eb = std::make_unique<Graphics::ElementBuffer>(indices, 6);

	vb->SetAttributes({
		{"aPos", Graphics::VertexAttributeType::VEC3F},
		{"aTexCoord", Graphics::VertexAttributeType::VEC2F},
	});

	va->SetVertexBuffer(std::move(vb));
	va->SetElementBuffer(std::move(eb));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Application::LoadContent()
{
	const std::string vertexShaderPath = Utils::SHADER_PATH + "getting_started.vert";
	const std::string fragmentShaderPath = Utils::SHADER_PATH + "getting_started.frag";

	shaderProgram = std::make_unique<Graphics::ShaderProgram>(
		vertexShaderPath, fragmentShaderPath);

	const std::string boxTexturePath = Utils::TEXTURE_PATH + "container.jpg";
	const std::string faceTexturePath = Utils::TEXTURE_PATH + "awesomeface.png";

	boxTexture = std::make_unique<Graphics::Texture>(
		content.GetTexture(boxTexturePath));

	faceTexture = std::make_unique<Graphics::Texture>(
		content.GetTexture(faceTexturePath));

	shaderProgram->Use();

	shaderProgram->SetInt("texture1", 0);
	shaderProgram->SetInt("texture2", 1);

	shaderProgram->UnUse();
}

void Application::UnloadContent()
{
	va = nullptr;
	shaderProgram = nullptr;
	content.Clear();
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

	boxTexture->BindAndActivate(0);
	faceTexture->BindAndActivate(1);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, window->GetElapsedTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	shaderProgram->Use();
	shaderProgram->SetMat4f("transform", trans);

	va->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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

	UnloadContent();
}
