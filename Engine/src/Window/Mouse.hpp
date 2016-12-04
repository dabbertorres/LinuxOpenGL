#ifndef DBR_GL_MOUSE_HPP
#define DBR_GL_MOUSE_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace dbr
{
	namespace gl
	{
		enum class MouseButton : decltype(GLFW_MOUSE_BUTTON_1)
		{
			Btn1 = GLFW_MOUSE_BUTTON_1,
			Btn2 = GLFW_MOUSE_BUTTON_2,
			Btn3 = GLFW_MOUSE_BUTTON_3,
			Btn4 = GLFW_MOUSE_BUTTON_4,
			Btn5 = GLFW_MOUSE_BUTTON_5,
			Btn6 = GLFW_MOUSE_BUTTON_6,
			Btn7 = GLFW_MOUSE_BUTTON_7,
			Btn8 = GLFW_MOUSE_BUTTON_8,

			Left   = GLFW_MOUSE_BUTTON_LEFT,
			Right  = GLFW_MOUSE_BUTTON_RIGHT,
			Middle = GLFW_MOUSE_BUTTON_MIDDLE,
		};
	}
}

#endif
