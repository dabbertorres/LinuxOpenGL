#ifndef DBR_MATH_HPP
#define DBR_MATH_HPP

namespace dbr
{
	namespace math
	{
		constexpr float PI = 3.14159265359;

		template<typename T>
		inline T lerp(T min, T max, double scale)
		{
			return (1.0 - scale) * min + scale * max;
		}
	}
}

#endif
