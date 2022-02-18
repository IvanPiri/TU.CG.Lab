#pragma once

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

		float mousePosX = 0.0f;
		float mousePosY = 0.0f;
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

		void SetMousePosition(const float x, const float y)
		{
			mousePosX = x;
			mousePosY = y;
		}

		void ResetState();

		[[nodiscard]] float GetMouseX() const { return mousePosX; }
		[[nodiscard]] float GetMouseY() const { return mousePosY; }
		[[nodiscard]] float GetScrollValue() const { return scrollWheelValue; }
	};
}
