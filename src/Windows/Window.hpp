#ifndef DBR_GL_WINDOWS_WINDOW_HPP
#define DBR_GL_WINDOWS_WINDOW_HPP

#pragma warning(push, 0)
#define WIN32_NEED_WINDOWING
#include "Windows.hpp"
#pragma warning(pop)

#include <cstddef>

namespace dbr
{
	namespace gl
	{
		namespace windows
		{
			class Window
			{
				public:
					Window(std::size_t width, std::size_t height);
					~Window();

					bool isOpen();
					void close();

				private:
					static bool classRegistered;

					HWND handle;
					HDC deviceContext;
			};
		}
	}
}

#endif
