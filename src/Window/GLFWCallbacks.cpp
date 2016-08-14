#include "GLFWCallbacks.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Window.hpp"

namespace dbr
{
	namespace gl
	{
		namespace
		{
			inline Window* pointerConvert(GLFWwindow* win)
			{
				return static_cast<Window*>(glfwGetWindowUserPointer(win));
			}
		}

		namespace cb
		{
			namespace window
			{
				void position(GLFWwindow* window, int x, int y)
				{
					auto* win = pointerConvert(window);
					win->moved(x, y);
				}

				void size(GLFWwindow* window, int x, int y)
				{
					auto* win = pointerConvert(window);
					win->resized(x, y);
				}

				void close(GLFWwindow* window)
				{
					auto* win = pointerConvert(window);
					win->closed();
				}

				void refresh(GLFWwindow* window)
				{
					auto* win = pointerConvert(window);
					win->refresh();
				}

				void focus(GLFWwindow* window, int f)
				{
					auto* win = pointerConvert(window);
					win->focusChange(f != 0 ? Window::Focus::Gain : Window::Focus::Lost);
				}

				void iconify(GLFWwindow* window, int i)
				{
					auto* win = pointerConvert(window);
					win->iconified(i != 0 ? Window::Iconify::Iconify : Window::Iconify::Restore);
				}

				void frameBufferSize(GLFWwindow* window, int x, int y)
				{
					auto* win = pointerConvert(window);
					win->frameBufferResized(x, y);
				}
			}

			namespace input
			{
				void mouseButton(GLFWwindow* window, int button, int action, int mod)
				{
					auto* win = pointerConvert(window);

				}

				void position(GLFWwindow* window, double x, double y)
				{
					auto* win = pointerConvert(window);
					win->mouseMoved(x, y);
				}

				void enter(GLFWwindow* window, int enter)
				{}

				void scroll(GLFWwindow* window, double x, double y)
				{}

				void key(GLFWwindow* window, int key, int scancode, int action, int mod)
				{}

				void unicode(GLFWwindow* window, unsigned int ch)
				{}

				void unicodeMod(GLFWwindow* window, unsigned int ch, int mod)
				{}

				void fileDrop(GLFWwindow* window, int count, const char** paths)
				{}

				void joystick(int joy, int event)
				{}
			}
		}
	}
}
