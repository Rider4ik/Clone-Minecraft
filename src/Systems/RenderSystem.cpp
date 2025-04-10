#include "RenderSystem.h"


RenderSystem::RenderSystem()
{
	glGenVertexArrays(1, &VAO); // для упорядочивания и хранения информации о вершинах (включая их атрибуты) и связанных с ними состояния
    glBindVertexArray(VAO); //  связываем vao  по индетификатору 
	addVertices
	    ({
		     0,  0.5f, 0,
		 -0.5f, -0.5f, 0,
		  0.5f, -0.5f, 0
	    });
}

RenderSystem::~RenderSystem()
{
	glDeleteBuffers(mBuffers.size(), mBuffers.data()); // очищаем память буфера 
	glBindVertexArray(0);// Разрыв связи c VAO

}

GLuint RenderSystem::loadShadersFile(std::string vertexFile, std::string fragmentFile)
{

	try {
		std::ifstream vertexShaderFile(vertexFile),
		              fragmentShaderFile(fragmentFile);
		
		std::string vertexShaderSourse = { std::istreambuf_iterator<char>(vertexShaderFile),
							   std::istreambuf_iterator<char>() },
			fragmentShaderSourse = { std::istreambuf_iterator<char>(fragmentShaderFile),
							   std::istreambuf_iterator<char>() };
		const GLchar* vertexShaderCode = vertexShaderSourse.c_str();
		const GLchar* fragmentShaderCode = fragmentShaderSourse.c_str();
		//TODO:w add func
		GLuint vertexShader = createShader(vertexShaderCode, 0);
		GLuint fragmentShader = createShader(fragmentShaderCode, 1);
		GLuint shader = glCreateProgram();
		RenderSystem::linkShader(shader, vertexShader, fragmentShader);
		return shader;

	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "EROR ::'Shader file are not loaded'\n";
		return NULL;
	}
}
// TODO : add optimization 
void RenderSystem::addVertices(const std::vector<float>& data)
{
	GLuint VBO;  // индитефекатор буфера вершин 
	glGenBuffers(1, &VBO);//генерация буфера
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // связывание буфера с vao
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float),data.data(), GL_STATIC_DRAW); // заполнение буфера данными
	glVertexAttribPointer(mBuffers.size(), 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Указываем, как интерпретировать данные из VBO в VAO
	mBuffers.push_back(VBO);

}

// TODO change 
void RenderSystem::drawCall()
{
	for (size_t i = 0; i < mBuffers.size(); i++)
	{
		glEnableVertexAttribArray(i); //  включаем атрибуты (vbo) vao  по индексу
	}
	glDrawArrays(GL_TRIANGLES,0,3);
	for (size_t i = 0; i < mBuffers.size(); i++)
	{
		glDisableVertexAttribArray(i); //  выключаем
	}
}

GLuint RenderSystem::createShader(const GLchar* shaderCode, GLuint type)
{
	GLuint shader = glCreateShader(type);
	GLint succes;
	GLchar infoLog[512];
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Fragment SHADER COMPILATION FAIL \n";
		std::cerr << infoLog << "\n";
		return NULL;
	}
	return shader;
}

void RenderSystem::linkShader(GLuint shader, GLuint vertexShader, GLuint fragmentShader)
{
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);
	GLint succes;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "SHADER LINK FAIL \n";
		std::cerr << infoLog << "\n";
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}



