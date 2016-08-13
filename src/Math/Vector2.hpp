#ifndef DBR_MATH_VECTOR2_HPP
#define DBR_MATH_VECTOR2_HPP

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
		using Vector2u = Vector2<unsigned int>;
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

		template<typename T, typename U>
		Vector2<T> operator*(U lhs, const Vector2<T>& rhs);

		template<typename T>
		T dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

		template<typename T>
		T cross(const Vector2<T>& lhs, const Vector2<T>& rhs);

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
			return std::sqrtf(x * x + y * y);
		}

		template<typename T>
		Vector2<T> unit(const Vector2<T>& vec)
		{
			auto len = vec.length();

			return{vec.x / len, vec.y / len};
		}

		template<typename T>
		Vector2<T> operator-(const Vector2<T>& vec)
		{
			return{-vec.x, -vec.y};
		}

		template<typename T>
		Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return{lhs.x + rhs.x, lhs.y + rhs.y};
		}

		template<typename T>
		Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return{lhs.x - rhs.x, lhs.y - rhs.y};
		}

		template<typename T, typename U>
		Vector2<T> operator*(const Vector2<T>& lhs, U rhs)
		{
			return{lhs.x * rhs, lhs.y * rhs};
		}

		template<typename T, typename U>
		inline Vector2<T> operator*(U lhs, const Vector2<T>& rhs)
		{
			return rhs * lhs;
		}

		template<typename T>
		T dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		template<typename T>
		T cross(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return lhs.x * rhs.y - lhs.y * rhs.x;
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
