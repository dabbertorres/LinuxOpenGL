#ifndef DBR_GL_WINDOW_WINDOW_HPP
#define DBR_GL_WINDOW_WINDOW_HPP

#include "Window/Event.hpp"

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

			void update();

			void clear(const Color& col = Color::Black());
			void draw();
			void display();

			bool isOpen();
			
			math::Vector2u windowSize() const;
			math::Vector2u bufferSize() const;

			Event<void(double, double)> mouseMove;

		private:
			GLFWwindow* window;
		};
	}
}

#endif
