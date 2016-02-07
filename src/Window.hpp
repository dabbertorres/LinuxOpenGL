#ifndef DBR_GL_WINDOW_HPP
#define DBR_GL_WINDOW_HPP

namespace dbr
{
	namespace gl
	{
		class Window
		{
			public:
				Window();
				~Window();

				bool isOpen();
				void close();
		};
	}
}

#endif
