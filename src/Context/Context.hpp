#ifndef DBR_GL_CONTEXT_IMPL_CONTEXT_HPP
#define DBR_GL_CONTEXT_IMPL_CONTEXT_HPP

namespace dbr
{
	namespace gl
	{
		namespace impl
		{
			template<typename I>
			class Context
			{
			public:
				Context() = default;
				~Context() = default;

				void activate()
				{
					impl.activate();
				}

				void deactivate()
				{
					impl.deactivate();
				}

				// let user access the implementation if necessary
				I& implementation()
				{
					return impl;
				}

				const I& implementation() const
				{
					return impl;
				}

			private:
				I impl;
			};
		}
	}
}

#endif
