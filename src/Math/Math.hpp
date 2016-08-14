#ifndef DBR_MATH_HPP
#define DBR_MATH_HPP

namespace dbr
{
	namespace math
	{
		constexpr float PI = 3.14159265359;

		template<typename T>
		inline T lerp(T min, T max, double f)
		{
			return (1.0 - f) * min + f * max;
		}
	}
}

#endif
