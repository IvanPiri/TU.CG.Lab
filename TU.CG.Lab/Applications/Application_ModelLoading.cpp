#include "Application_ModelLoading.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <string>

#include "../Utils/Constants.hpp"
#include "../Utils/ContentManager.hpp"

namespace Applications
{
	Application_ModelLoading::Application_ModelLoading()
		: IApplication(), lightPos(1.2f, 1.0f, 2.0f)
	{
		window = std::make_unique<Utils::Window>("TU.CG.Lab", 800, 600);
	}

	void Application_ModelLoading::Initialize()
	{
		window->ActivateInputFor(this);

		camera = std::make_unique<Utils::Camera>(
			glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

		constexpr float lightVertices[] =
		{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		lightVa = std::make_unique<Graphics::VertexArray>();

		auto lightVb = std::make_unique<Graphics::VertexBuffer>(
			lightVertices, static_cast<unsigned>(sizeof lightVertices));

		lightVb->SetAttributes({
			{"aPos", Graphics::VertexAttributeType::VEC3F},
		});

		lightVa->SetVertexBuffer(std::move(lightVb));

		glEnable(GL_DEPTH_TEST);
	}

	void Application_ModelLoading::LoadContent()
	{
		const std::string modelPath = Utils::MODEL_PATH + "backpack/backpack.model";

		backpack = std::make_unique<Graphics::Model>(
			std::move(content.GetModel(modelPath)));

		const std::string vertexShaderPath = Utils::SHADER_PATH + "lighting.vert";
		const std::string fragmentShaderPath = Utils::SHADER_PATH + "lighting.frag";

		shaderProgram = std::make_unique<Graphics::ShaderProgram>(
			vertexShaderPath, fragmentShaderPath);

		shaderProgram->Use();

		shaderProgram->SetInt("material.diffuse", 0);
		shaderProgram->SetInt("material.specular", 1);
		shaderProgram->SetFloat("material.shininess", 32.0f);

		shaderProgram->SetVec3f("light.ambient", glm::vec3(0.2f));
		shaderProgram->SetVec3f("light.diffuse", glm::vec3(0.5f));
		shaderProgram->SetVec3f("light.specular", glm::vec3(1.0f));
		shaderProgram->SetVec3f("light.position", lightPos);

		shaderProgram->UnUse();

		const std::string lightCubeVertexShaderPath = Utils::SHADER_PATH + "light_source.vert";
		const std::string lightCubeFragmentShaderPath = Utils::SHADER_PATH + "light_source.frag";

		lightCubeShaderProgram = std::make_unique<Graphics::ShaderProgram>(
			lightCubeVertexShaderPath, lightCubeFragmentShaderPath);

		lightCubeShaderProgram->Use();

		lightCubeShaderProgram->SetVec3f("lightColor", glm::vec3(1.0f));

		lightCubeShaderProgram->UnUse();
	}

	void Application_ModelLoading::UnloadContent()
	{
		shaderProgram = nullptr;
		lightCubeShaderProgram = nullptr;
		backpack = nullptr;
		content.Clear();
	}

	void Application_ModelLoading::Update(const float deltaTime)
	{
		if (inputManager.IsKeyDown(Input::Keys::ESCAPE))
			window->SetShouldClose(true);

		camera->Update(deltaTime, inputManager);

		inputManager.ResetState();
	}

	void Application_ModelLoading::Render() const
	{
		glClearColor(0.393f, 0.585f, 0.930f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->Use();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		const glm::mat4 view = camera->GetViewMatrix();
		const glm::mat4 projection = glm::perspective(
			glm::radians(camera->zoom),
			window->GetSize().x / window->GetSize().y,
			0.1f, 100.0f);

		const glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(model));

		shaderProgram->SetMat3f("normal", normalMatrix);
		shaderProgram->SetMat4f("model", model);
		shaderProgram->SetMat4f("view", view);
		shaderProgram->SetMat4f("projection", projection);
		shaderProgram->SetVec3f("viewPos", camera->position);

		backpack->Draw(*shaderProgram);

		shaderProgram->UnUse();

		// ---

		lightCubeShaderProgram->Use();
		lightVa->Bind();

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightCubeShaderProgram->SetMat4f("model", model);
		lightCubeShaderProgram->SetMat4f("view", view);
		lightCubeShaderProgram->SetMat4f("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightCubeShaderProgram->UnUse();
	}

	void Application_ModelLoading::Run()
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
}
