#ifndef DBR_GL_COMPONENT_HPP
#define DBR_GL_COMPONENT_HPP

namespace dbr
{
	namespace gl
	{
		class Component
		{
			public:
				using Id = unsigned int;

				Component(Id id);

				Id ID() const;

			private:
				Id id;
		};
	}
}

#endif
