#include "Camera.hpp"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

namespace Utils
{
	Camera::Camera(const glm::vec3 position, const glm::vec3 worldUp, const float maxZoom)
		: position(position), front(0.0f, 0.0f, -1.0f), up(0.0f), right(0.0f),
		worldUp(worldUp), yaw(-90.0f), pitch(0.0f), movementSpeed(2.5f),
		mouseSensitivity(0.1f), zoom(maxZoom), maxZoom(maxZoom),
		isUserControlEnabled(true)
	{
	}

	void Camera::Update(
		const float deltaTime, Input::InputManager& inputManager)
	{
		if (!isUserControlEnabled)
			return;

		const float velocity = movementSpeed * deltaTime;
		const glm::vec3 forwardBackwardMovement = front * velocity;
		const glm::vec3 leftRightMovement = right * velocity;

		if (inputManager.IsKeyDown(Input::Keys::W))
			position += forwardBackwardMovement;

		if (inputManager.IsKeyDown(Input::Keys::S))
			position -= forwardBackwardMovement;

		if (inputManager.IsKeyDown(Input::Keys::A))
			position -= leftRightMovement;

		if (inputManager.IsKeyDown(Input::Keys::D))
			position += leftRightMovement;

		const glm::vec2 currentCursorPos = inputManager.GetCursorPosition();

		static float lastX = 0.0f;
		static float lastY = 0.0f;

		float xOffset = currentCursorPos.x - lastX;
		float yOffset = lastY - currentCursorPos.y;
		lastX = currentCursorPos.x;
		lastY = currentCursorPos.y;

		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		pitch = std::clamp(pitch, -89.0f, 89.0f);

		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));

		zoom -= inputManager.GetScrollValue();
		zoom = std::clamp(zoom, 1.0f, maxZoom);
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(position, position + front, up);
	}
}
