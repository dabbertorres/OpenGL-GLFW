#include "Window.hpp"

namespace swift
{
	Window::Window()
	:	Window(3, 2)
	{}
	
	Window::Window(int contextMajor, int contextMinor)
	:	context{contextMajor, contextMinor},
		window(nullptr)
	{
		glfwInit();
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context[0]);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context[1]);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	Window::~Window()
	{
		glfwTerminate();
	}
	
	bool Window::create(const Vector<int, 2>& res, const std::string& title, int monitor, bool fullscreen)
	{
		window = glfwCreateWindow(res[0], res[1], title.c_str(), nullptr, nullptr);
		
		// should throw exception instead
		if(!window)
			return false;
		
		glfwMakeContextCurrent(window);
		
		return true;
	}
}
