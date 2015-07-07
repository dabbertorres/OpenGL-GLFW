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
			int context[2];
			
			GLFWwindow* window;
	};
}

#endif // SWIFT_WINDOW_HPP
