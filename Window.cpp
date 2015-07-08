#include "Window.hpp"

#include <stdexcept>

namespace swift
{
	Window::Window()
	:	Window(3, 2)
	{}
	
	Window::Window(int contextMajor, int contextMinor)
	:	context{contextMajor, contextMinor},
		window(nullptr),
		isFullscreen(false)
	{
		if(!numOfWindows)
		{
			GLint sts = glfwInit();
			
			if(!sts)
				throw std::runtime_error("glfwInit failed!");
		}
		
		++numOfWindows;
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context[0]);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context[1]);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	Window::~Window()
	{
		--numOfWindows;
		
		if(!numOfWindows)
			glfwTerminate();
	}
	
	bool Window::create(const Vector<int, 2>& res, const std::string& t, int mon, bool fs)
	{
		title = t;
		isFullscreen = fs;
		window = glfwCreateWindow(res[0], res[1], title.c_str(), nullptr, nullptr);
		
		// should throw exception instead
		if(!window)
				throw std::runtime_error("Could not create the window.");
		
		glfwMakeContextCurrent(window);
		
		return true;
	}
	
	unsigned int Window::numOfWindows = 0;
}
