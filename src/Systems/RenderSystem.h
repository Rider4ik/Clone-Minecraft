#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <gl.h>
#include <GLFW/glfw3.h>
#include <vector>

class RenderSystem
{
private:
    GLuint VAO;
    std::vector<GLuint> mBuffers;
    static GLuint createShader(const GLchar* shaderCode, GLuint type);
    static void linkShader(GLuint chader, GLuint vertexShader, GLuint fragmentShader);
public:
    RenderSystem();
    ~RenderSystem();
    static GLuint loadShadersFile(std::string vertexFile, std::string fragmentFile);
    void addVertices(const std::vector<float>& data);
    void drawCall(); 
   
};

