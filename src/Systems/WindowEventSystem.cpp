#include "WindowEventSystem.h"

void WindowEventSystem::window_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void WindowEventSystem::initialize(GLFWwindow* window)
{
	glfwSetWindowSizeCallback(window, window_size_callback);
}

void WindowEventSystem::window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
