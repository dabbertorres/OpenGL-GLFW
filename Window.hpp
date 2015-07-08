#ifndef SWIFT_WINDOW_HPP
#define SWIFT_WINDOW_HPP

#include <string>

#include <GL/glew.h>	// GLEW include MUST go before GLFW include

#include <GLFW/glfw3.h>

#include "Vector.hpp"

namespace swift
{
	class Window
	{
		public:
			Window();
			Window(int contextMajor, int contextMinor);
			~Window();
			
			bool create(const Vector<int, 2>& res, const std::string& title, int monitor, bool fullscreen);
		
		private:
			// keeps a count of the number of windows constructed (not created).
			// if == 0 when a window is constructed, glfwInit is called
			// if == 0 when destroying a window, glfwTerminate is called
			static unsigned int numOfWindows;
			
			int context[2];
			
			GLFWwindow* window;
			std::string title;
			bool isFullscreen;
	};
}

#endif // SWIFT_WINDOW_HPP
