#ifndef DBR_ENG_ECS_RENDERABLE_HPP
#define DBR_ENG_ECS_RENDERABLE_HPP

#include "Graphics/Types.hpp"

#include "ecs/Component.hpp"

namespace dbr
{
	namespace eng
	{
        namespace ecs
        {
            class Renderable : public Component
            {
            public:
                Renderable(Id id, gfx::HandleI bufferHandle);
                ~Renderable();

            private:
                gfx::HandleI bufferHandle;
            };
        }
	}
}

#endif
