#include "Window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "GLFWCallbacks.hpp"

#include <map>

#include "opengl/gl_glCore33.hpp"

#include "Engine.hpp"

namespace
{
	gl::exts::LoadTest glLoaded;
}

namespace dbr
{
	namespace eng
	{
        namespace win
        {
            Window::Window()
                : window(nullptr)
            {}

            Window::~Window()
            {
                close();
            }

            void Window::open(uint32_t width, uint32_t height, const std::string& title, bool fullscreen, uint32_t monitorIdx)
            {
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, gl::TRUE_);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? Engine::instance.get(monitorIdx) : nullptr, nullptr);
                activate();

                if (!glLoaded)
                {
                    if (!(glLoaded = gl::sys::LoadFunctions()))
                        throw std::runtime_error("Failed to acquire OpenGL functions");
                }

                glfwSetWindowUserPointer(window, this);

                // window callbacks
                glfwSetWindowPosCallback(window, cb::win::moved);
                glfwSetWindowSizeCallback(window, cb::win::size);
                glfwSetWindowCloseCallback(window, cb::win::close);
                glfwSetWindowRefreshCallback(window, cb::win::refresh);
                glfwSetWindowFocusCallback(window, cb::win::focus);
                glfwSetWindowIconifyCallback(window, cb::win::stateChange);
                glfwSetFramebufferSizeCallback(window, cb::win::frameBufferSize);

                // input callbacks
                glfwSetMouseButtonCallback(window, cb::input::mouseButton);
                glfwSetCursorPosCallback(window, cb::input::moved);
                glfwSetCursorEnterCallback(window, cb::input::enter);
                glfwSetScrollCallback(window, cb::input::scroll);
                glfwSetKeyCallback(window, cb::input::key);
                glfwSetCharCallback(window, cb::input::unicode);
                glfwSetCharModsCallback(window, cb::input::unicodeMod);
                glfwSetDropCallback(window, cb::input::fileDrop);
    //			glfwSetJoystickCallback(cb::input::joystick);
            }

            void Window::close()
            {
                if (window != nullptr)
                    glfwDestroyWindow(window);

                window = nullptr;
            }

            void Window::activate()
            {
                glfwMakeContextCurrent(window);
            }

            void Window::deactivate()
            {
                glfwMakeContextCurrent(nullptr);
            }

            void Window::lockCursor(bool lock)
            {
                glfwSetInputMode(window, GLFW_CURSOR, lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            }

            void Window::pollEvents()
            {
                glfwPollEvents();
            }

            void Window::waitEvents()
            {
                glfwWaitEvents();
            }

            void Window::clear(const gfx::Color& col)
            {
                gl::ClearColor(col.rf(), col.gf(), col.bf(), col.af());
                gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
            }

            void Window::draw()
            {

            }

            void Window::display()
            {
                glfwSwapBuffers(window);
            }

            bool Window::isOpen()
            {
                return !glfwWindowShouldClose(window);
            }

            util::Size Window::windowSize() const
            {
                int w = 0;
                int h = 0;
                glfwGetWindowSize(window, &w, &h);

                return{static_cast<util::Size::Type>(w), static_cast<util::Size::Type>(h)};
            }

            util::Size Window::bufferSize() const
            {
                int w = 0;
                int h = 0;
                glfwGetFramebufferSize(window, &w, &h);

                return{static_cast<util::Size::Type>(w), static_cast<util::Size::Type>(h)};
            }
        }
	}
}
