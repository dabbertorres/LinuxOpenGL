#ifndef DBR_MATH_HPP
#define DBR_MATH_HPP

namespace dbr
{
	namespace math
	{
		constexpr double PI = 3.141592653589793238463;
		constexpr float PIf = 3.14159265358979f;

		template<typename T>
		inline T lerp(T min, T max, double f)
		{
			return (1.0 - f) * min + f * max;
		}
	}
}

#endif
