#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}	
}

Window::Window(const std::string& title, int width, int height)
{
	if (!glfwInit())
	{
		//TO DO : Change 
		throw std::runtime_error("EROR, GLFW AND GLEW NOT INITIALIZATE");
	}
	else
	{
		window = std::unique_ptr<GLFWwindow, GLFWWindowDeleter>(
			glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), GLFWWindowDeleter());

		glfwMakeContextCurrent(window.get());
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
		}
		renderSystem = std::make_unique<RenderSystem>();
	    WindowEventSystem::initialize(window.get());
		loop(); 
	}
}



void Window::loop()
{
	while (!glfwWindowShouldClose(window.get()))
	{
		glClearColor(1, 0.7, 0, 1);  
		glClear(GL_COLOR_BUFFER_BIT); 
		renderSystem->drawCall();
      	glfwSwapBuffers(window.get()); 
		glfwPollEvents();		
	}
}

