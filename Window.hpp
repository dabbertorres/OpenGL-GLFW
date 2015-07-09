#ifndef SWIFT_WINDOW_HPP
#define SWIFT_WINDOW_HPP

#include <string>

#include <GL/glew.h>	// GLEW include MUST go before GLFW include

#include <GLFW/glfw3.h>

#include "Types.hpp"

#include "Monitor.hpp"

#include "Vector.hpp"

namespace swift
{
	class Window
	{
		public:
			Window();
			Window(uint contextMajor, uint contextMinor);
			~Window();
			
			bool create(const Vector<uint, 2>& res, const std::string& title, uint monitor = 0, bool fullscreen = false);
			
			// generally only needed for fullscreen windows
			// otherwise, the desktop's current video mode is used
			void setVideoMode(const Monitor::VideoMode& vm);
			
			// activates/deactivates the window's OpenGL context
			// the window must be active to draw to it
			void setActive(bool cc);
			
			// returns whether this Window's context is active or not
			bool isActive() const;
			
			bool isOpen() const;
			
			// calling either of these two functions causes the callback functions for 
			// each respective event to be called.
			// these may only be called from the main thread.
			void pollEvents();
			void waitEvents();
		
		private:
			// keeps a count of the number of windows constructed (not created).
			// if == 0 when a window is constructed, glfwInit is called
			// if == 0 when destroying a window, glfwTerminate is called
			static uint numOfWindows;
			
			uint context[2];
			
			GLFWwindow* window;
			std::string title;
			bool isFullscreen;
			
			Vector<uint, 2> resolution;
	};
}

#endif // SWIFT_WINDOW_HPP
