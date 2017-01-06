#ifndef DBR_ENG_GFX_SHADER_HPP
#define DBR_ENG_GFX_SHADER_HPP

#include "Types.hpp"

#include <istream>

namespace dbr
{
    namespace eng
    {
        namespace gfx
        {
            class Shader
            {
            public:
                enum class Type
                {
                    Vertex,
                    Fragment,
                    Geometry,
                };

                Shader(Type t);
                ~Shader();

                void load(std::istream& in);

                HandleU handle() const;
                Type type() const;

            private:
                HandleU handleVal;
                Type typeVal;
            };
        }
    }
}

#endif
