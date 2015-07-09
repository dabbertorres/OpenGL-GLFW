#include "Window.hpp"

#include <stdexcept>

namespace swift
{
	Window::Window()
	:	Window(3, 2)
	{}
	
	Window::Window(uint contextMajor, uint contextMinor)
	:	context{contextMajor, contextMinor},
		window(nullptr),
		isFullscreen(false)
	{
		if(!numOfWindows)
		{
			GLint sts = glfwInit();
	
			if(!sts)
				throw std::runtime_error("glfwInit failed!");
			
			// setup GLEW
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			
			if(err != GLEW_OK)
				throw std::runtime_error("glewInit failed!");
		}
		
		++numOfWindows;
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context[0]);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context[1]);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		
		--numOfWindows;
		
		if(!numOfWindows)
			glfwTerminate();
	}
	
	bool Window::create(const Vector<uint, 2>& res, const std::string& t, uint mon, bool fs)
	{
		title = t;
		isFullscreen = fs;
		window = glfwCreateWindow(res[0], res[1], title.c_str(), nullptr, nullptr);
		
		// should throw exception instead
		if(!window)
			throw std::runtime_error("Could not create the window.");
		
		return true;
	}
	
	void Window::setVideoMode(const Monitor::VideoMode& vm)
	{
		glfwWindowHint(GLFW_BLUE_BITS, vm.blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, vm.greenBits);
		glfwWindowHint(GLFW_RED_BITS, vm.redBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vm.refreshRate);
	}
	
	void Window::setActive(bool cc)
	{
		glfwMakeContextCurrent(cc ? window : nullptr);
	}
	
	bool Window::isActive() const
	{
		return window == glfwGetCurrentContext();
	}
	
	bool Window::isOpen() const
	{
		
	}
	
	void Window::pollEvents()
	{
		glfwPollEvents();
	}
	
	void Window::waitEvents()
	{
		glfwWaitEvents();
	}
	
	unsigned int Window::numOfWindows = 0;
}
