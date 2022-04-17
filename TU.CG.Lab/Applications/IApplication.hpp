#pragma once

#include "../Input/InputManager.hpp"

namespace Applications
{
	class IApplication
	{
	protected:
		IApplication() = default;
	public:
		virtual ~IApplication() = default;
		IApplication(const IApplication& other) = default;
		IApplication& operator=(const IApplication& other) = default;
		IApplication(IApplication&& other) = default;
		IApplication& operator=(IApplication&& other) = default;

		virtual Input::InputManager& GetInputManager() = 0;
	};
}
