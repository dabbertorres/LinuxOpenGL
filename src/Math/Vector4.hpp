#ifndef DBR_MATH_VECTOR4_HPP
#define DBR_MATH_VECTOR4_HPP

namespace dbr
{
	namespace math
	{
		template<typename T>
		struct Vector4
		{
			Vector4();
			Vector4(T x, T y, T z, T w);

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
		Vector4<T> unit(const Vector4<T>& vec);

		template<typename T>
		Vector4<T> operator-(const Vector4<T>& vec);

		template<typename T>
		Vector4<T> operator+(const Vector4<T>& lhs, const Vector4<T>& rhs);

		template<typename T>
		Vector4<T> operator-(const Vector4<T>& lhs, const Vector4<T>& rhs);

		template<typename T, typename U>
		Vector4<T> operator*(const Vector4<T>& lhs, U rhs);

		template<typename T, typename U>
		Vector4<T> operator*(U lhs, const Vector4<T>& rhs);

		template<typename T>
		T dot(const Vector4<T>& lhs, const Vector4<T>& rhs);

		template<typename T>
		bool operator==(const Vector4<T>& lhs, const Vector4<T>& rhs);

		template<typename T>
		bool operator!=(const Vector4<T>& lhs, const Vector4<T>& rhs);

		template<typename T>
		Vector4<T>::Vector4()
		:	x(0),
			y(0),
			z(0),
			w(0)
		{}

		template<typename T>
		Vector4<T>::Vector4(T x, T y, T z, T w)
		:	x(x),
			y(y),
			z(z),
			w(w)
		{}

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

		template<typename T, typename U>
		Vector4<T> operator*(const Vector4<T>& lhs, U rhs)
		{
			return{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
		}

		template<typename T, typename U>
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
	}
}

#endif
