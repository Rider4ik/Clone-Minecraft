#pragma once
#include "WindowEventSystem.h"
#include <RenderSystem.h>
#include <string>
#include <iostream>


class Window
{
private:
	struct GLFWWindowDeleter {
		void operator()(GLFWwindow* window) const {
			glfwTerminate();
			glfwDestroyWindow(window);
		}
	};
	std::unique_ptr<GLFWwindow, GLFWWindowDeleter> window;
	std::unique_ptr<RenderSystem> renderSystem;
public:
	Window(){};
	Window(const std::string& title, int width, int height);
	void loop();
	~Window(){};
};

