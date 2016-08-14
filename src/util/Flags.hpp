#ifndef DBR_UTIL_FLAGS_HPP
#define DBR_UTIL_FLAGS_HPP

#include <type_traits>

namespace dbr
{
	namespace util
	{
		template<typename E>
		class Flags
		{
		public:
			Flags(E e)
				: value(e)
			{}

			Flags& operator=(E e)
			{
				value = e;
			}

			operator E() const
			{
				return value;
			}

		private:
			typename std::underlying_type<E>::type value;
		};

		template<typename E>
		Flags<E> operator|(Flags<E> lhs, Flags<E> rhs)
		{
			return lhs.value | rhs.value;
		}
	}
}

#endif
