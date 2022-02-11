#pragma once

struct GLFWwindow;
class Application;

namespace Utils
{
	class Window
	{
	private:
		GLFWwindow* window;
		unsigned width;
		unsigned height;

		static void FramebufferSizeCallback(GLFWwindow* window, int initialWidth, int initialHeight);
	public:
		Window(const char* title, unsigned width, unsigned height);
		Window(const Window& other) = delete;
		Window& operator=(Window const& other) = delete;
		Window(Window&& other) = delete;
		Window& operator=(Window&& other) = delete;
		~Window();

		void SwapBuffers() const;
		void PollEvents();
		void ActivateInputFor(Application* app) const;

		[[nodiscard]] bool GetShouldClose() const;
		void SetShouldClose(bool value) const;

		[[nodiscard]] float GetElapsedTime() const;

		[[nodiscard]] unsigned GetWidth() const { return width; }
		[[nodiscard]] unsigned GetHeight() const { return height; }
	};
}
