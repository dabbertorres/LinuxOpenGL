#ifndef DBR_ENG_GFX_TYPES_HPP
#define DBR_ENG_GFX_TYPES_HPP

#include "opengl/gl_glCore33.hpp"

// read-only opengl handle structs

namespace dbr
{
    namespace eng
    {
        namespace gfx
        {
            struct HandleI
            {
            public:
                HandleI(GLint h = 0)
                    : handle(h)
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
                HandleU(GLuint h = 0)
                    : handle(h)
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
}

#endif
