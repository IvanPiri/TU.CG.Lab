#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

#include "Keys.hpp"
#include "MouseButtons.hpp"

namespace Input
{
	class InputManager
	{
	private:
		std::unordered_map<Keys, bool> keyMap;
		std::unordered_map<MouseButtons, bool> buttonMap;

		glm::vec2 cursorPosition = glm::vec2(0.0f);
		float scrollWheelValue = 0.0f;
	public:
		void PressKey(Keys key);
		void ReleaseKey(Keys key);
		void PressButton(MouseButtons button);
		void ReleaseButton(MouseButtons button);
		void Scroll(float value);

		bool IsKeyDown(Keys key);
		bool IsButtonDown(MouseButtons button);
		// TODO: IsKeyPressed, IsButtonPressed

		void SetMousePosition(const glm::vec2 pos)
		{
			cursorPosition = pos;
		}

		void ResetState();

		[[nodiscard]] glm::vec2 GetCursorPosition() const { return cursorPosition; }
		[[nodiscard]] float GetScrollValue() const { return scrollWheelValue; }
	};
}
