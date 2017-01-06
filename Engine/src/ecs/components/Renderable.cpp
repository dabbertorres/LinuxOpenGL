#include "Renderable.hpp"

#include "opengl/gl_glCore33.hpp"

namespace dbr
{
	namespace eng
	{
        namespace ecs
        {
            Renderable::Renderable(Id id, gfx::HandleI bufferHandle)
                : Component(id),
                bufferHandle(bufferHandle)
            {}

            Renderable::~Renderable()
            {

            }
        }
	}
}
