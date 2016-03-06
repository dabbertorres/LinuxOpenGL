#ifndef DBR_GL_RENDERABLE_HPP
#define DBR_GL_RENDERABLE_HPP

#include "Core.hpp"

#include "ecs/Component.hpp"

namespace dbr
{
	namespace gl
	{
		class Renderable : public Component
		{
			public:
				Renderable(Id id, HandleI bufferHandle);
				~Renderable();

			private:
				HandleI bufferHandle;
		};
	}
}

#endif
