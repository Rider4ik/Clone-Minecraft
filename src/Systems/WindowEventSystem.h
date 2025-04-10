#pragma once
#include "RenderSystem.h"
#include <unordered_map>

// TODO:: ADD key callbacks 
class WindowEventSystem
{ 
private:
    std::unordered_map<int, void(*)()> keys;
public:
    static void window_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void initialize(GLFWwindow* window);
    static void window_size_callback(GLFWwindow* window, int width, int height);
};

