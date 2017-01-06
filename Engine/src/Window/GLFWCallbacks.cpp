#include "GLFWCallbacks.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Window.hpp"

namespace dbr
{
    namespace eng
    {
        namespace win
        {
            namespace
            {
                Window* pointerConvert(GLFWwindow* win)
                {
                    return static_cast<Window*>(glfwGetWindowUserPointer(win));
                }
            }

            namespace cb
            {
                namespace win
                {
                    void moved(GLFWwindow* window, int x, int y)
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
                        win->focusChange(f == GLFW_TRUE ? Events::Focus::Gain : Events::Focus::Lost);
                    }

                    void stateChange(GLFWwindow* window, int i)
                    {
                        auto* win = pointerConvert(window);
                        win->stateChange(i == GLFW_TRUE ? Events::State::Iconify : Events::State::Restore);
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
                        win->mouseButton(static_cast<MouseButton>(button), static_cast<Events::Button>(action), static_cast<Modifiers>(mod));
                    }

                    void moved(GLFWwindow* window, double x, double y)
                    {
                        auto* win = pointerConvert(window);
                        win->mouseMoved(x, y);
                    }

                    void enter(GLFWwindow* window, int enter)
                    {
                        auto* win = pointerConvert(window);
                        win->mouseEnter(enter == GLFW_TRUE);
                    }

                    void scroll(GLFWwindow* window, double x, double y)
                    {
                        auto* win = pointerConvert(window);
                        win->mouseScroll(x, y);
                    }

                    void key(GLFWwindow* window, int key, int scancode, int action, int mod)
                    {
                        auto* win = pointerConvert(window);
                        win->key(static_cast<Keyboard>(key), scancode, static_cast<Events::Button>(action), static_cast<Modifiers>(mod));
                    }

                    void unicode(GLFWwindow* window, unsigned int ch)
                    {
                        auto* win = pointerConvert(window);
                        win->unicodeText(ch);
                    }

                    void unicodeMod(GLFWwindow* window, unsigned int ch, int mod)
                    {
                        auto* win = pointerConvert(window);
                        win->unicodeTextModified(ch, static_cast<Modifiers>(mod));
                    }

                    void fileDrop(GLFWwindow* window, int count, const char** paths)
                    {
                        auto* win = pointerConvert(window);

                        std::vector<std::string> v{paths, paths + count};
                        win->fileDrop(v);
                    }

                    /*void joystick(int id, int event)
                    {
                        Window::joystick(id, event);
                    }*/
                }
            }
        }
    }
}
