#pragma once

#include <glm/glm.hpp>

#include "../Input/InputManager.hpp"

namespace Utils
{
	class Camera
	{
	private:
		glm::vec2 previousCursorPos;
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;

		float yaw;
		float pitch;

		float movementSpeed;
		float mouseSensitivity;

		float zoom;
		float maxZoom;

		bool isUserControlEnabled;

		Camera(glm::vec3 position, glm::vec3 worldUp, float maxZoom);

		void Update(float deltaTime, Input::InputManager& inputManager);

		[[nodiscard]] glm::mat4 GetViewMatrix() const;
	};
}
