#ifndef DBR_ENG_ECS_COMPONENT_HPP
#define DBR_ENG_ECS_COMPONENT_HPP

#include "util/Types.hpp"

namespace dbr
{
    namespace eng
    {
        namespace ecs
        {
            class Component
            {
            public:
                using Id = size_t;

                Component(Id id);

                Id ID() const;

            private:
                Id id;
            };
        }
    }
}

#endif
