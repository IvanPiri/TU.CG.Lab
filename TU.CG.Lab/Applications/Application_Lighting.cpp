#include "Application_Lighting.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <string>

#include "../Utils/Constants.hpp"
#include "../Utils/ContentManager.hpp"

namespace Applications
{
	Application_Lighting::Application_Lighting() : IApplication(), lightPos(1.2f, 1.0f, 2.0f)
	{
		window = std::make_unique<Utils::Window>("TU.CG.Lab", 800, 600);
	}

	void Application_Lighting::Initialize()
	{
		window->ActivateInputFor(this);

		camera = std::make_unique<Utils::Camera>(
			glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

		constexpr float objectVertices[] =
		{
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		};

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

		va = std::make_unique<Graphics::VertexArray>();

		auto vb = std::make_unique<Graphics::VertexBuffer>(
			objectVertices, static_cast<unsigned>(sizeof objectVertices));

		vb->SetAttributes({
			{"aPos", Graphics::VertexAttributeType::VEC3F},
			{"aNormal", Graphics::VertexAttributeType::VEC3F},
			{"aTexCoord", Graphics::VertexAttributeType::VEC2F},
		});

		va->SetVertexBuffer(std::move(vb));

		lightVa = std::make_unique<Graphics::VertexArray>();

		auto lightVb = std::make_unique<Graphics::VertexBuffer>(
			lightVertices, static_cast<unsigned>(sizeof lightVertices));

		lightVb->SetAttributes({
			{"aPos", Graphics::VertexAttributeType::VEC3F},
		});

		lightVa->SetVertexBuffer(std::move(lightVb));

		glEnable(GL_DEPTH_TEST);
	}

	void Application_Lighting::LoadContent()
	{
		//constexpr glm::vec3 lightColor(1.0f);

		const std::string vertexShaderPath = Utils::SHADER_PATH + "lighting.vert";
		const std::string fragmentShaderPath = Utils::SHADER_PATH + "lighting.frag";

		shaderProgram = std::make_unique<Graphics::ShaderProgram>(
			vertexShaderPath, fragmentShaderPath);

		shaderProgram->Use();

		shaderProgram->SetVec3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		shaderProgram->SetVec3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		shaderProgram->SetVec3f("material.specular", glm::vec3(0.5f));
		shaderProgram->SetFloat("material.shininess", 32.0f);

		//shaderProgram->SetVec3f("light.ambient", glm::vec3(0.2f));
		//shaderProgram->SetVec3f("light.diffuse", glm::vec3(0.5f));
		shaderProgram->SetVec3f("light.specular", glm::vec3(1.0f));
		shaderProgram->SetVec3f("light.position", lightPos);

		shaderProgram->UnUse();

		const std::string lightVertexShaderPath = Utils::SHADER_PATH + "light_source.vert";
		const std::string lightFragmentShaderPath = Utils::SHADER_PATH + "light_source.frag";

		lightShaderProgram = std::make_unique<Graphics::ShaderProgram>(
			lightVertexShaderPath, lightFragmentShaderPath);

		//lightShaderProgram->Use();

		//lightShaderProgram->SetVec3f("lightColor", lightColor);

		//lightShaderProgram->UnUse();
	}

	void Application_Lighting::UnloadContent()
	{
		va = nullptr;
		lightVa = nullptr;
		shaderProgram = nullptr;
		lightShaderProgram = nullptr;
		content.Clear();
	}

	void Application_Lighting::Update(const float deltaTime)
	{
		if (inputManager.IsKeyDown(Input::Keys::ESCAPE))
			window->SetShouldClose(true);

		camera->Update(deltaTime, inputManager);

		inputManager.ResetState();
	}

	void Application_Lighting::Render() const
	{
		glClearColor(0.393f, 0.585f, 0.930f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightColor;
		lightColor.x = sin(window->GetElapsedTime() * 2.0f);
		lightColor.y = sin(window->GetElapsedTime() * 0.7f);
		lightColor.z = sin(window->GetElapsedTime() * 1.3f);

		const glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		const glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		shaderProgram->Use();
		va->Bind();

		shaderProgram->SetVec3f("light.ambient", ambientColor);
		shaderProgram->SetVec3f("light.diffuse", diffuseColor);

		glm::mat4 model(1.0f);

		const glm::mat4 view = camera->GetViewMatrix();
		const glm::mat4 projection = glm::perspective(
			glm::radians(camera->zoom),
			window->GetSize().x / window->GetSize().y,
			0.1f, 100.0f);
		const glm::mat3 normal = glm::inverseTranspose(glm::mat3(model));

		shaderProgram->SetMat4f("model", model);
		shaderProgram->SetMat4f("view", view);
		shaderProgram->SetMat4f("projection", projection);
		shaderProgram->SetMat3f("normal", normal);
		shaderProgram->SetVec3f("viewPos", camera->position);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		va->Unbind();
		shaderProgram->UnUse();

		// ---

		lightShaderProgram->Use();
		lightVa->Bind();

		lightShaderProgram->SetVec3f("lightColor", lightColor);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShaderProgram->SetMat4f("model", model);
		lightShaderProgram->SetMat4f("view", view);
		lightShaderProgram->SetMat4f("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightVa->Unbind();
		lightShaderProgram->UnUse();
	}

	void Application_Lighting::Run()
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
