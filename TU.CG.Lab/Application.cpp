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

	camera = std::make_unique<Utils::Camera>(
		glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

	constexpr float vertices[] =
	{
		// positions          // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	};

	va = std::make_unique<Graphics::VertexArray>();
	auto vb = std::make_unique<Graphics::VertexBuffer>(vertices, sizeof vertices);

	vb->SetAttributes({
		{"aPos", Graphics::VertexAttributeType::VEC3F},
		{"aTexCoord", Graphics::VertexAttributeType::VEC2F},
	});

	va->SetVertexBuffer(std::move(vb));

	glEnable(GL_DEPTH_TEST);
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

	camera->Update(deltaTime, inputManager);

	inputManager.ResetState();
}

void Application::Render() const
{
	glClearColor(0.393f, 0.585f, 0.930f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	boxTexture->BindAndActivate(0);
	faceTexture->BindAndActivate(1);

	shaderProgram->Use();

	va->Bind();

	constexpr glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f),
	};

	const glm::mat4 view = camera->GetViewMatrix();
	const glm::mat4 projection = glm::perspective(
		glm::radians(camera->zoom), window->GetSize().x / window->GetSize().y,
		0.1f, 100.0f);

	shaderProgram->SetMat4f("view", view);
	shaderProgram->SetMat4f("projection", projection);

	for (unsigned i = 0; i < 10; ++i)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, cubePositions[i]);
		const float angle = 20.0f * static_cast<float>(i);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		shaderProgram->SetMat4f("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

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
