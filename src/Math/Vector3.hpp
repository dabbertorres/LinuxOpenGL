#ifndef DBR_MATH_VECTOR3_HPP
#define DBR_MATH_VECTOR3_HPP

namespace dbr
{
	namespace math
	{
		// a vector 3 has a 4th member, w, like a Vector4.
		// However, it is not used in any calculations.
		// It exists only to pad the structure to word boundaries
		// it is initialized to 1.0, and does not change
		template<typename T>
		struct Vector3
		{
			Vector3();
			Vector3(T x, T y, T z);

			float length() const;

			T x;
			T y;
			T z;
			const T w;
		};

		using Vector3i = Vector3<int>;
		using Vector3u = Vector3<unsigned int>;
		using Vector3f = Vector3<float>;

		template<typename T>
		Vector3<T> unit(const Vector3<T>& vec);

		template<typename T>
		Vector3<T> operator-(const Vector3<T>& vec);

		template<typename T>
		Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		Vector3<T> operator-(const Vector3<T>& lhs, const Vector3<T>& rhs);

		// cross product
		template<typename T>
		Vector3<T> operator*(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T, typename U>
		Vector3<T> operator*(const Vector3<T>& lhs, U rhs);

		template<typename T, typename U>
		Vector3<T> operator*(U lhs, const Vector3<T>& rhs);

		template<typename T>
		T dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		Vector3<T>::Vector3()
		:	x(0),
			y(0),
			z(0),
			w(1)
		{}

		template<typename T>
		Vector3<T>::Vector3(T x, T y, T z)
		:	x(x),
			y(y),
			z(z),
			w(1)
		{}

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

		template<typename T>
		Vector3<T> operator*(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return{lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
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
		bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
		}

		template<typename T>
		bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return !(lhs == rhs);
		}
	}
}

#endif
