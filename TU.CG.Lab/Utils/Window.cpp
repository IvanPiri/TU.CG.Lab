#include "Window.hpp"

#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Application.hpp"

namespace Utils
{
	Window::Window(const char* title, const unsigned initialWidth, const unsigned initialHeight)
	{
		if (initialWidth == 0)
			throw std::exception("Screen width must be a positive integer.");

		if (initialHeight == 0)
			throw std::exception("Screen height must be a positive integer.");

		if (glfwInit() != GLFW_TRUE)
			throw std::exception("Failed to initialize GLFW.");

		width = initialWidth;
		height = initialHeight;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr)
		{
			glfwTerminate();
			throw std::exception("Failed to create a GLFW window.");
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glfwTerminate();
			throw std::exception("Failed to initialize GLAD.");
		}

		glViewport(0, 0, width, height);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::ActivateInputFor(Application* app) const
	{
		glfwSetWindowUserPointer(window, app);

		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	}

	bool Window::GetShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::SetShouldClose(const bool value) const
	{
		glfwSetWindowShouldClose(window, value);
	}

	float Window::GetElapsedTime() const
	{
		return static_cast<float>(glfwGetTime());
	}

	void Window::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}
}
