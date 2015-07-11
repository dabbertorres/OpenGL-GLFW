#ifndef SWIFT_WINDOW_HPP
#define SWIFT_WINDOW_HPP

#include <string>
#include <set>
#include <unordered_map>
#include <functional>

#include <GL/glew.h>	// GLEW include MUST go before GLFW include

#include <GLFW/glfw3.h>

#include "Types.hpp"
#include "Vector.hpp"

#include "Event.hpp"

#include "Monitor.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace swift
{
	class Window
	{
		public:
			// Key pressed, bitmask of modifier keys held when press occured, scancode
			using KeyPressEvent = Event<Keyboard::Key, int, int>;
			
			// Key released, bitmask of modifier keys held when release occured, scancode
			using KeyReleaseEvent = Event<Keyboard::Key, int, int>;
			
			// Unicode codepoint
			using UnicodeEvent = Event<uint>;
			
			// true if entered, false if left
			using MouseEnteredEvent = Event<bool>;
			
			// x, y
			using MouseMovedEvent = Event<double, double>;
			
			// Button pressed, bitmask of modifier keys when press occured
			using MousePressEvent = Event<Mouse::Button, int>;
			
			// Button pressed, bitmask of modifier keys when release occured
			using MouseReleaseEvent = Event<Mouse::Button, int>;
			
			// x offset, y offset
			using ScrollEvent = Event<double, double>;
			
			Window();
			Window(uint contextMajor, uint contextMinor);
			
			Window(const Window& other) = delete;
			
			~Window();

			void create(const Vector<uint, 2>& res, const std::string& title, uint monitor = 0, bool fullscreen = false);

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
			
			KeyPressEvent keyPressEvent;
			KeyReleaseEvent keyReleaseEvent;
			UnicodeEvent unicodeEvent;
			MouseEnteredEvent mouseEnteredEvent;
			MouseMovedEvent mouseMovedEvent;
			MousePressEvent mousePressEvent;
			MouseReleaseEvent mouseReleaseEvent;
			ScrollEvent scrollEvent;
			
		private:
			// C doesn't like member functions. These aren't member functions.
			static void keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
			static void unicodeCallback(GLFWwindow* win, uint codepoint);
			static void mouseEnteredCallback(GLFWwindow* win, int entered);
			static void mouseMovedCallback(GLFWwindow* win, double x, double y);
			static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
			static void scrollCallback(GLFWwindow* win, double x, double y);
			 
			// if size == 0 when a window is constructed, glfwInit is called
			// if size == 0 when destroying a window, glfwTerminate is called
			static uint numOfWindows;
			
			// keeps pointers to all Window instances by their GLFWwindow pointer.
			// used for accessing the correct Window from event callback functions
			static std::unordered_map<GLFWwindow*, Window*> windows;
			
			uint context[2];

			GLFWwindow* window;
			std::string title;
			bool isFullscreen;

			Vector<uint, 2> resolution;
	};
}

#endif // SWIFT_WINDOW_HPP
