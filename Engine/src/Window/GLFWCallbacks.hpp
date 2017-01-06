#ifndef DBR_ENG_WINDOW_GLFW_CALLBACKS_HPP
#define DBR_ENG_WINDOW_GLFW_CALLBACKS_HPP

struct GLFWwindow;

namespace dbr
{
	namespace eng
	{
        namespace win
        {
            class Window;

            namespace cb
            {
                namespace win
                {
                    void moved(GLFWwindow* window, int x, int y);
                    void size(GLFWwindow* window, int x, int y);
                    void close(GLFWwindow* window);
                    void refresh(GLFWwindow* window);
                    void focus(GLFWwindow* window, int f);
                    void stateChange(GLFWwindow* window, int i);
                    void frameBufferSize(GLFWwindow* window, int x, int y);
                }

                namespace input
                {
                    void mouseButton(GLFWwindow* window, int button, int action, int mod);
                    void moved(GLFWwindow* window, double x, double y);
                    void enter(GLFWwindow* window, int enter);
                    void scroll(GLFWwindow* window, double x, double y);
                    void key(GLFWwindow* window, int key, int scancode, int action, int mod);
                    void unicode(GLFWwindow* window, unsigned int ch);
                    void unicodeMod(GLFWwindow* window, unsigned int ch, int mod);
                    void fileDrop(GLFWwindow* window, int count, const char** paths);
//  				void joystick(int id, int event);
                }
            }
        }
	}
}

#endif
