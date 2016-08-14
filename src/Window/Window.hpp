#ifndef DBR_GL_WINDOW_WINDOW_HPP
#define DBR_GL_WINDOW_WINDOW_HPP

#include "Window/Event.hpp"
#include "Window/Mouse.hpp"
#include "Window/Keyboard.hpp"

#include "Graphics/Color.hpp"
#include "Math/Vector2.hpp"

struct GLFWwindow;

namespace dbr
{
	namespace gl
	{
		class Window
		{
		public:
			Window();
			~Window();

			void open(std::size_t width, std::size_t height, const std::string& title, bool fullscreen = false, std::size_t monitorIdx = 0);
			void close();

			void activate();
			void deactivate();

			void pollEvents();

			void clear(const Color& col = Color::Black());
			void draw();
			void display();

			bool isOpen();
			
			math::Vector2u windowSize() const;
			math::Vector2u bufferSize() const;

			// window state events
			enum class Focus
			{
				Gain,
				Lost,
			};

			enum class Iconify
			{
				Iconify,
				Restore,
			};

			Event<void(int, int)> moved;
			Event<void(int, int)> resized;
			Event<void()> closed;
			Event<void()> refresh;
			Event<void(Focus)> focusChange;
			Event<void(Iconify)> iconified;
			Event<void(int, int)> frameBufferResized;

			// input events
			enum class Action
			{
				Press,
				Release,
			};

			Event<void(MouseButton, Action, ModifersFlags)> mouseButton;
			Event<void(double, double)> mouseMoved;

		private:
			GLFWwindow* window;
		};
	}
}

#endif
