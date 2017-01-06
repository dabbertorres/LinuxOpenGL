#ifndef DBR_ENG_MATH_HPP
#define DBR_ENG_MATH_HPP

#pragma warning(push, 0)
#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace dbr
{
    namespace eng
    {
        namespace math
        {
            // single dimension linear interpolation
            // ie: find the value (f * 100)% between min and max
            template<typename T, typename Float>
            T lerp(T min, T max, Float f)
            {
                return static_cast<T>((1.0 - f) * min + f * max);
            }

            // two dimensional linear interpolation
            // ie: find the y-value of desired given (x, y) pairs lower and upper
            glm::vec2::value_type lerp(glm::vec2 lower, glm::vec2 upper, glm::vec2::value_type desired)
            {
                return lower.y + (desired - lower.x) * (upper.y - lower.y) / (upper.x - lower.x);
            }
        }
    }
}

#endif
