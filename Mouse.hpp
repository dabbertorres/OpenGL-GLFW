#ifndef SWIFT_MOUSE_HPP
#define SWIFT_MOUSE_HPP

#include <GLFW/glfw3.h>

namespace swift
{
	class Mouse
	{
		public:
			enum class Button : int
			{
				Left = GLFW_MOUSE_BUTTON_1,
				Right = GLFW_MOUSE_BUTTON_2,
				Middle = GLFW_MOUSE_BUTTON_3,
				Extra1 = GLFW_MOUSE_BUTTON_4,
				Extra2 = GLFW_MOUSE_BUTTON_5,
				Extra3 = GLFW_MOUSE_BUTTON_6,
				Extra4 = GLFW_MOUSE_BUTTON_7,
				Extra5 = GLFW_MOUSE_BUTTON_8,
			};
			
		private:
			Mouse() = default;
	};
}

#endif // SWIFT_MOUSE_HPP
