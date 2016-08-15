#ifndef DBR_MATH_VECTOR3_HPP
#define DBR_MATH_VECTOR3_HPP

#include "Matrix.hpp"

namespace dbr
{
	namespace math
	{
		template<typename T>
		struct Vector3
		{
			Vector3()
				: x(0),
				y(0),
				z(0),
				w(1)
			{}

			Vector3(T x, T y, T z)
				: x(x),
				y(y),
				z(z),
				w(1)
			{}

			float length() const;

			T x;
			T y;
			T z;
		};

		using Vector3i = Vector3<int>;
		using Vector3u = Vector3<unsigned int>;
		using Vector3f = Vector3<float>;

		template<typename T>
		inline float Vector3<T>::length() const
		{
			float x2 = x * x;
			float y2 = y * y;
			float z2 = z * z;

			return std::sqrtf(x2 + y2 + z2);
		}

		template<typename T>
		Vector3<T> unit(const Vector3<T>& vec)
		{
			auto len = vec.length();

			return{vec.x / len, vec.y / len, vec.z / len};
		}

		template<typename T>
		Vector3<T> operator-(const Vector3<T>& vec)
		{
			return{-vec.x, -vec.y, -vec.z};
		}

		template<typename T>
		Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
		}

		template<typename T>
		Vector3<T> operator-(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
		}

		template<typename T, typename U>
		Vector3<T> operator*(const Vector3<T>& lhs, U rhs)
		{
			return{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
		}

		template<typename T, typename U>
		inline Vector3<T> operator*(U lhs, const Vector3<T>& rhs)
		{
			return rhs * lhs;
		}

		template<typename T>
		T dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		template<typename T>
		Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return{lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
		}

		template<typename T>
		bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
		}

		template<typename T>
		bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T, typename U>
		auto operator*(const Matrix<U, 3, 3>& mat, const Vector3<T>& vec)
		{
			auto x = vec.x * mat(0, 0) + vec.y * mat(1, 0) + vec.z * mat(2, 0);
			auto y = vec.x * mat(0, 1) + vec.y * mat(1, 1) + vec.z * mat(2, 1);
			auto z = vec.x * mat(0, 2) + vec.y * mat(1, 2) + vec.z * mat(2, 2);

			return Vector3<decltype(x)>{x, y, z};
		}
	}
}

#endif
