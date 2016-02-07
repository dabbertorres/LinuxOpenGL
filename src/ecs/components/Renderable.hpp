#ifndef DBR_GL_RENDERABLE_HPP
#define DBR_GL_RENDERABLE_HPP

#include "Component.hpp"

namespace dbr
{
	namespace gl
	{
		class Renderable : public Component
		{
			public:
				Renderable(Id id);
				~Renderable();
		};
	}
}

#endif
