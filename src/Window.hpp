#ifndef DBR_GL_WINDOW_HPP
#define DBR_GL_WINDOW_HPP

#ifdef _WIN32
#	include "Windows/Window.hpp"
#else
#	include "Linux/Window.hpp"
#endif

namespace dbr
{
	namespace gl
	{
		namespace impl
		{
			template<typename Impl>
			class Window
			{
				public:
					Window();
					~Window();

					bool isOpen();
					void close();

					void clear();
					void display();

				private:
					Impl impl;
			};
		}
#ifdef _WIN32
		using Window = impl::Window<windows::Window>;
#else

#endif
	}
}

#endif
