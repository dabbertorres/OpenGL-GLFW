#include <iostream>
#include <string>

#include <GL/glew.h>	// GLEW include MUST go before GLFW include

#include <GLFW/glfw3.h>

#include "Vector.hpp"
#include "Triangle.hpp"

int main(int argc, char** argv)
{
	constexpr const char* vertShaderSrc =	"#version 150 core\n"
											"in vec2 position;"
											"void main()"
											"{"
											"gl_Position = vec4(position, 0.0, 1.0);"
											"}";

	constexpr const char* fragShaderSrc =	"#version 150 core\n"
											"out vec4 outColor;"
											"void main()"
											"{"
											"outColor = vec4(1.0, 1.0, 1.0, 1.0);"
											"}";

	glfwInit();

	// setup OpenGL context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// setup window options
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "StickerOnPlane", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// we can use Vertex Array Objects to save links between attributes and Vertex Buffer Objects
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// now, whenever we bind a VAO, every time we call glVertexAttribPointer, that information is stored in the last bound VAO

	// create our Vertex Buffer Object for using vertices
	GLuint vbo;
	glGenBuffers(1, &vbo);

	float vertices[] =
	{
		0.0, 0.5,
		0.5, -0.5,
		-0.5, -0.5,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setup shaders
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	// check for shader compile errors
	GLint vertStatus;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertStatus);

	GLint fragStatus;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragStatus);

	if(vertStatus != GL_TRUE)
	{
		char buf[512];
		glGetShaderInfoLog(vertShader, 512, NULL, buf);

		std::cerr << "Compile error in vertex shader:\n";
		std::cerr << buf << '\n';
		return 1;
	}

	if(fragStatus != GL_TRUE)
	{
		char buf[512];
		glGetShaderInfoLog(fragShader, 512, NULL, buf);

		std::cerr << "Compile error in fragment shader:\n";
		std::cerr << buf << '\n';
		return 2;
	}

	// combine shaders into gpu program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);

	// specify output buffer for fragment shader
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	// link the program
	glLinkProgram(shaderProgram);

	// use the program!
	// note: only one program can be active at one time, just like with VBOs
	glUseProgram(shaderProgram);

	// need to say how the vertex shader is going to receive input from us
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	// clean up
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragShader);
	glDeleteShader(vertShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);

	glfwTerminate();

	return 0;
}
