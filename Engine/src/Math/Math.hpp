#ifndef DBR_MATH_HPP
#define DBR_MATH_HPP

#pragma warning(push, 0)
#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace dbr
{
	namespace math
	{
		template<typename T>
		T lerp(T min, T max, double f)
		{
			return (1.0 - f) * min + f * max;
		}
	}
}

#endif
