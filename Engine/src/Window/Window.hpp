#ifndef DBR_ENG_WINDOW_WINDOW_HPP
#define DBR_ENG_WINDOW_WINDOW_HPP

#include "Window/Mouse.hpp"
#include "Window/Keyboard.hpp"

#include "Graphics/Color.hpp"

#include "util/Event.hpp"
#include "util/Types.hpp"

struct GLFWwindow;

namespace dbr
{
	namespace eng
	{
        namespace win
        {
            namespace Events
            {
                enum class Focus
                {
                    Gain,
                    Lost,
                };

                enum class State
                {
                    Iconify,
                    Restore,
                };

                enum class Button : decltype(GLFW_PRESS)
                {
                    Press   = GLFW_PRESS,
                    Release = GLFW_RELEASE,
                    Repeat  = GLFW_REPEAT,
                };
            }

            class Window
            {
            public:
                Window();
                ~Window();

                void open(uint32_t width, uint32_t height, const std::string& title, bool fullscreen = false, uint32_t monitorIdx = 0);
                void close();

                void activate();
                void deactivate();

                void lockCursor(bool lock = true);

                void pollEvents();
                void waitEvents();

                void clear(const gfx::Color& col = gfx::Color::Black());
                void draw();
                void display();

                bool isOpen();

                util::Size windowSize() const;
                util::Size bufferSize() const;

                // window state events
                util::Event<void(int x, int y)> moved;
                util::Event<void(int w, int h)> resized;
                util::Event<void()> closed;
                util::Event<void()> refresh;
                util::Event<void(Events::Focus f)> focusChange;
                util::Event<void(Events::State s)> stateChange;
                util::Event<void(int w, int h)> frameBufferResized;

                // input events
                util::Event<void(MouseButton btn, Events::Button action, Modifiers mods)> mouseButton;
                util::Event<void(double x, double y)> mouseMoved;
                util::Event<void(bool entered)> mouseEnter;
                util::Event<void(double x, double y)> mouseScroll;
                util::Event<void(Keyboard key, int scancode, Events::Button action, Modifiers mods)> key;
                util::Event<void(unsigned int unicode)> unicodeText;
                util::Event<void(unsigned int unicode, Modifiers mods)> unicodeTextModified;
                util::Event<void(std::vector<std::string> paths)> fileDrop;

                // joysticks aren't owned by any single window
//  			static Event<void(int id, int event)> joystick;

            private:
                GLFWwindow* window;
            };
        }
	}
}

#endif
