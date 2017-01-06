#include "Component.hpp"

namespace dbr
{
    namespace eng
    {
        namespace ecs
        {
            Component::Component(Id id)
                : id(id)
            {}

            Component::Id Component::ID() const
            {
                return id;
            }
        }
    }
}
