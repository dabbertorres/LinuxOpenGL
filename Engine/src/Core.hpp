#ifndef DBR_GL_CORE_HPP
#define DBR_GL_CORE_HPP

#include "opengl/gl_glCore33.hpp"

namespace dbr
{
	namespace gl
	{
		// read-only opengl handle structs

		struct HandleI
		{
			public:
				HandleI(GLint h)
				:	handle(h)
				{}

				operator GLint() const
				{
					return handle;
				}

			private:
				GLint handle;
		};

		struct HandleU
		{
			public:
				HandleU(GLuint h)
				:	handle(h)
				{}

				operator GLuint() const
				{
					return handle;
				}

			private:
				GLuint handle;
		};
	}
}

#endif
