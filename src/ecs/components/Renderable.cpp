#include "Renderable.hpp"

#include "opengl/gl_glCore33.hpp"

namespace dbr
{
	namespace gl
	{
		Renderable::Renderable(Id id, HandleI bufferHandle)
		:	Component(id),
			bufferHandle(bufferHandle)
		{}

		Renderable::~Renderable()
		{
			
		}
	}
}