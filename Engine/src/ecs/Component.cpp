#include "Component.hpp"

namespace dbr
{
	namespace gl
	{
		Component::Component(Id id)
		:	id(id)
		{}

		Component::Id Component::ID() const
		{
			return id;
		}
	}
}
