#ifndef DBR_MATH_ANGLE_HPP
#define DBR_MATH_ANGLE_HPP

#include "Math/Math.hpp"

namespace dbr
{
	namespace math
	{
		template<typename T>
		struct Angle
		{
		public:
			operator T() const
			{
				return value;
			}

			template<typename U>
			operator Angle<U> const
			{
				return static_cast<U>(value);
			}

			Angle operator+(Angle other)
			{
				return value + other.value;
			}

			Angle operator-(Angle other)
			{
				return value - other.value;
			}

			Angle operator*(double scal)
			{
				return value * scal;
			}

			Angle operator/(double scal)
			{
				return value / scal;
			}

			Angle& operator+=(Angle other)
			{
				value += other.value;
				return *this;
			}

			Angle operator-=(Angle other)
			{
				value -= other.value;
				return *this;
			}

			Angle operator*=(double scal)
			{
				value *= scal;
				return *this;
			}

			Angle operator/=(double scal)
			{
				value /= scal;
				return *this;
			}

		private:
			Angle(T v)
				: value(v)
			{}

			// stored as radians
			T value;
		};

		namespace literals
		{
			template<typename T>
			Angle<T> operator "" deg(T t)
			{
				return t / 180.0 * PI;
			}

			template<typename T>
			Angle<T> operator "" rad(T t)
			{
				return t;
			}
		}
	}
}

#endif
