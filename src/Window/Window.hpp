#ifndef DBR_GL_WINDOW_WINDOW_HPP
#define DBR_GL_WINDOW_WINDOW_HPP

#include "Window/Event.hpp"
#include "Window/Mouse.hpp"
#include "Window/Keyboard.hpp"

#include "Graphics/Color.hpp"

#include "util/Types.hpp"

struct GLFWwindow;

namespace dbr
{
	namespace gl
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

			enum class Button : int
			{
				Press = GLFW_PRESS,
				Release = GLFW_RELEASE,
				Repeat = GLFW_REPEAT,
			};
		}

		class Window
		{
		public:
			Window();
			~Window();

			void open(std::size_t width, std::size_t height, const std::string& title, bool fullscreen = false, std::size_t monitorIdx = 0);
			void close();

			void activate();
			void deactivate();

			void lockCursor(bool lock = true);

			void pollEvents();
			void waitEvents();

			void clear(const Color& col = Color::Black());
			void draw();
			void display();

			bool isOpen();
			
			Size windowSize() const;
			Size bufferSize() const;

			// window state events
			Event<void(int x, int y)> moved;
			Event<void(int w, int h)> resized;
			Event<void()> closed;
			Event<void()> refresh;
			Event<void(Events::Focus f)> focusChange;
			Event<void(Events::State s)> stateChange;
			Event<void(int w, int h)> frameBufferResized;

			// input events
			Event<void(MouseButton btn, Events::Button action, Modifiers mods)> mouseButton;
			Event<void(double x, double y)> mouseMoved;
			Event<void(bool entered)> mouseEnter;
			Event<void(double x, double y)> mouseScroll;
			Event<void(Keyboard key, int scancode, Events::Button action, Modifiers mods)> key;
			Event<void(unsigned int unicode)> unicodeText;
			Event<void(unsigned int unicode, Modifiers mods)> unicodeTextModified;
			Event<void(std::vector<std::string> paths)> fileDrop;
			
			// joysticks aren't owned by any single window
//			static Event<void(int id, int event)> joystick;

		private:
			GLFWwindow* window;
		};
	}
}

#endif
