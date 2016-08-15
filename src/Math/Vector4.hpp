#ifndef DBR_MATH_VECTOR4_HPP
#define DBR_MATH_VECTOR4_HPP

#include "Matrix.hpp"

namespace dbr
{
	namespace math
	{
		template<typename T>
		struct Vector4
		{
			Vector4()
				: x(0),
				y(0),
				z(0),
				w(0)
			{}

			Vector4(T x, T y, T z)
				: x(x),
				y(y),
				z(z),
				w(1)
			{}

			Vector4(T x, T y, T z, T w)
				: x(x),
				y(y),
				z(z),
				w(w)
			{}

			float length() const;

			T x;
			T y;
			T z;
			T w;
		};

		using Vector4i = Vector4<int>;
		using Vector4u = Vector4<unsigned int>;
		using Vector4f = Vector4<float>;

		template<typename T>
		inline float Vector4<T>::length() const
		{
			float x2 = x * x;
			float y2 = y * y;
			float z2 = z * z;
			float w2 = w * w;

			return std::sqrtf(x2 + y2 + z2 + w2);
		}

		template<typename T>
		Vector4<T> unit(const Vector4<T>& vec)
		{
			auto len = vec.length();

			return{vec.x / len, vec.y / len, vec.z / len, vec.w / len};
		}

		template<typename T>
		Vector4<T> operator-(const Vector4<T>& vec)
		{
			return{-vec.x, -vec.y, -vec.z, -vec.w};
		}

		template<typename T>
		Vector4<T> operator+(const Vector4<T>& lhs, const Vector4<T>& rhs)
		{
			return{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
		}

		template<typename T>
		Vector4<T> operator-(const Vector4<T>& lhs, const Vector4<T>& rhs)
		{
			return{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
		}

		template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
		Vector4<T> operator*(const Vector4<T>& lhs, U rhs)
		{
			return{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
		}

		template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
		inline Vector4<T> operator*(U lhs, const Vector4<T>& rhs)
		{
			return rhs * lhs;
		}

		template<typename T>
		T dot(const Vector4<T>& lhs, const Vector4<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		template<typename T>
		bool operator==(const Vector4<T>& lhs, const Vector4<T>& rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
		}

		template<typename T>
		bool operator!=(const Vector4<T>& lhs, const Vector4<T>& rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T, typename U>
		auto operator*(const Matrix<U, 4, 4>& mat, const Vector4<T>& vec)
		{
			auto x = vec.x * mat(0, 0) + vec.y * mat(1, 0) + vec.z * mat(2, 0) + vec.w * mat(3, 0);
			auto y = vec.x * mat(0, 1) + vec.y * mat(1, 1) + vec.z * mat(2, 1) + vec.w * mat(3, 1);
			auto z = vec.x * mat(0, 2) + vec.y * mat(1, 2) + vec.z * mat(2, 2) + vec.w * mat(3, 2);
			auto w = vec.x * mat(0, 3) + vec.y * mat(1, 3) + vec.z * mat(2, 3) + vec.w * mat(3, 3);

			return Vector4<decltype(x)>{x, y, z, w};
		}
	}
}

#endif
