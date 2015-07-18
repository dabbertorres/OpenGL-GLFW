#include "Window.hpp"

#include <stdexcept>
#include <thread>

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

		{
			std::lock_guard<std::mutex> windowsLock(windowStaticLock);
			++numOfWindows;
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context[0]);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context[1]);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	Window::~Window()
	{
		if(window)
		{
			// remove glfw event callbacks
			{
				std::lock_guard<std::mutex> windowsLock(windowStaticLock);
				windows.erase(window);
			}
			
			glfwSetKeyCallback(window, nullptr);
			glfwSetCharCallback(window, nullptr);
			glfwSetCursorEnterCallback(window, nullptr);
			glfwSetCursorPosCallback(window, nullptr);
			
			glfwDestroyWindow(window);
		}
		
		{
			std::lock_guard<std::mutex> windowsLock(windowStaticLock);
			--numOfWindows;
		}
		
		if(!numOfWindows)
			glfwTerminate();
	}

	void Window::create(const Vector<uint, 2>& res, const std::string& t, const Monitor& mon, bool fs)
	{
		title = t;
		isFullscreen = fs;
		
		window = glfwCreateWindow(res[0], res[1], title.c_str(), mon.monitor, nullptr);

		if(!window)
			throw std::runtime_error("Could not create the window.");
		
		{
			std::lock_guard<std::mutex> windowsLock(windowStaticLock);
			windows.emplace(window, this);
		}
		
		glfwSetKeyCallback(window, &keyboardCallback);
		glfwSetCharCallback(window, &unicodeCallback);
		glfwSetCursorEnterCallback(window, &mouseEnteredCallback);
		glfwSetCursorPosCallback(window, &mouseMovedCallback);
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
		return window;
	}
	
	void Window::clear()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::draw()
	{
		
	}

	void Window::display()
	{
		glfwSwapBuffers(window);
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	void Window::waitEvents()
	{
		glfwWaitEvents();
	}
	
	void Window::keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		std::lock_guard<std::mutex> windowsLock(windowStaticLock);
		
		switch(action)
		{
			case GLFW_RELEASE:
				windows[win]->keyReleaseEvent(static_cast<Keyboard::Key>(key), mods, scancode);
				break;
			
			case GLFW_PRESS:
				windows[win]->keyPressEvent(static_cast<Keyboard::Key>(key), mods, scancode);
				break;
			
			default:
				break;
		}
	}
	
	void Window::unicodeCallback(GLFWwindow* win, uint codepoint)
	{
		std::lock_guard<std::mutex> windowsLock(windowStaticLock);
		windows[win]->unicodeEvent(codepoint);
	}
	
	void Window::mouseEnteredCallback(GLFWwindow* win, int entered)
	{
		std::lock_guard<std::mutex> windowsLock(windowStaticLock);
		windows[win]->mouseEnteredEvent(entered);
	}
	
	void Window::mouseMovedCallback(GLFWwindow* win, double x, double y)
	{
		std::lock_guard<std::mutex> windowsLock(windowStaticLock);
		windows[win]->mouseMovedEvent(x, y);
	}
	
	void Window::mouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
	{
		std::lock_guard<std::mutex> windowsLock(windowStaticLock);
		switch(action)
		{
			case GLFW_RELEASE:
				windows[win]->mousePressEvent(static_cast<Mouse::Button>(button), mods);
				break;
				
			case GLFW_PRESS:
				windows[win]->mouseReleaseEvent(static_cast<Mouse::Button>(button), mods);
				break;
				
			default:
				break;
		}
	}
	
	void Window::scrollCallback(GLFWwindow* win, double x, double y)
	{
		std::lock_guard<std::mutex> windowsLock(windowStaticLock);
		windows[win]->scrollEvent(x, y);
	}
	
	uint Window::numOfWindows = 0;
	std::unordered_map<GLFWwindow*, Window*> Window::windows;
	std::mutex Window::windowStaticLock;
}
