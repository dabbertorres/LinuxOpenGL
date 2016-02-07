#ifndef DBR_MATH_VECTOR4_HPP
#define DBR_MATH_VECTOR4_HPP

#include <cstddef>

namespace dbr
{
	namespace math
	{
		template<typename T>
		struct Vector2
		{
			Vector2();
			Vector2(T x, T y);

			float length() const;
			
			T x;
			T y;
		};

		using Vector2i = Vector2<int>;
		using Vector2u = Vector2<std::size_t>;
		using Vector2f = Vector2<float>;

		template<typename T>
		Vector2<T> unit(const Vector2<T>& vec);

		template<typename T>
		Vector2<T> operator-(const Vector2<T>& vec);

		template<typename T>
		Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);

		template<typename T>
		Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);

		template<typename T, typename U>
		Vector2<T> operator*(const Vector2<T>& lhs, U rhs);

		template<typename T>
		T dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

		template<typename T>
		bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

		template<typename T>
		bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs);

		template<typename T>
		Vector2<T>::Vector2()
		:	x(0),
			y(0)
		{}

		template<typename T>
		Vector2<T>::Vector2(T x, T y)
		:	x(x),
			y(y)
		{}

		template<typename T>
		inline float Vector2<T>::length() const
		{
			float x2 = x * x;
			float y2 = y * y;

			return std::sqrtf(x2 + y2);
		}

		template<typename T>
		Vector2<T> unit(const Vector2<T>& vec)
		{
			auto len = vec.length();

			return {vec.x / len, vec.y / len};
		}

		template<typename T>
		Vector2<T> operator-(const Vector2<T>& vec)
		{
			return {-vec.x, -vec.y};
		}

		template<typename T>
		Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return {lhs.x + rhs.x, lhs.y + rhs.y};
		}

		template<typename T>
		Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return {lhs.x - rhs.x, lhs.y - rhs.y};
		}

		template<typename T, typename U>
		Vector2<T> operator*(const Vector2<T>& lhs, U rhs)
		{
			return {lhs.x * rhs, lhs.y * rhs};
		}

		template<typename T>
		T dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		template<typename T>
		bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}

		template<typename T>
		bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return !(lhs == rhs);
		}
	}
}

#endif