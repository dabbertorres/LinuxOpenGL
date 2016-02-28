#ifndef DBR_MATH_QUATERNION_HPP
#define DBR_MATH_QUATERNION_HPP

#include <cmath>

#include "Vector3.hpp"

namespace dbr
{
	namespace math
	{
		template<typename T>
		class Quaternion
		{
			public:
				// creates a Quaternion from an Axis-Angle pair, with the angle in radians
				template<typename V>
				static Quaternion fromAxisAngle(const Vector3<V>& axis, float angle);
				
				Quaternion();
				Quaternion(T x, T y, T z);
				Quaternion(T w, T x, T y, T z);

				Quaternion conjugate() const;
				Quaternion normal() const;
				T norm() const;

				template<typename V>
				Vector3<V> rotate(const Vector3<V>& vector) const;

				T w;
				T x;
				T y;
				T z;
		};

		using Quaternionf = Quaternion<float>;
		using Quaterniond = Quaternion<double>;

		template<typename T>
		Quaternion<T> operator+(const Quaternion<T>& lhs, const Quaternion<T>& rhs);

		template<typename T>
		Quaternion<T> operator-(const Quaternion<T>& lhs, const Quaternion<T>& rhs);

		template<typename T>
		Quaternion<T> operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs);

		template<typename T>
		Quaternion<T> operator*(const Quaternion<T>& quat, T scal);

		template<typename T>
		Quaternion<T> operator*(T scal, const Quaternion<T>& quat);

		template<typename T>
		Quaternion<T>& operator+=(Quaternion<T>& lhs, const Quaternion<T>& rhs);

		template<typename T>
		Quaternion<T>& operator-=(Quaternion<T>& lhs, const Quaternion<T>& rhs);

		template<typename T>
		Quaternion<T>& operator*=(Quaternion<T>& lhs, const Quaternion<T>& rhs);

		template<typename T>
		Quaternion<T>& operator*=(Quaternion<T>& quat, T scal);

		template<typename T>
		template<typename V>
		Quaternion<T> Quaternion<T>::fromAxisAngle(const Vector3<V>& axis, float angle)
		{
			// make sure axis is a unit vector
			if(axis.length() != 1)
				axis = unit(axis);

			Quaternion<T> ret;

			float halfAngle = angle / 2.f;
			float sin = std::sin(halfAngle);

			ret.w = std::cos(halfAngle);
			ret.x = static_cast<T>(axis.x * sin);
			ret.y = static_cast<T>(axis.y * sin);
			ret.z = static_cast<T>(axis.z * sin);

			return ret;
		}

		template<typename T>
		Quaternion<T>::Quaternion()
		:	w(0),
			x(0),
			y(0),
			z(0)
		{}

		template<typename T>
		Quaternion<T>::Quaternion(T x, T y, T z)
		:	w(0),
			x(x),
			y(y),
			z(z)
		{}

		template<typename T>
		Quaternion<T>::Quaternion(T w, T x, T y, T z)
		:	w(w),
			x(x),
			y(y),
			z(z)
		{}

		template<typename T>
		Quaternion<T> Quaternion<T>::conjugate() const
		{
			return {w, -x, -y, -z};
		}

		template<typename T>
		Quaternion<T> Quaternion<T>::normal() const
		{
			auto n = norm();

			return {w / n, x / n, y / n, z / n};
		}

		template<typename T>
		T Quaternion<T>::norm() const
		{
			T w2 = w * w;
			T x2 = x * x;
			T y2 = y * y;
			T z2 = z * z;
			
			return std::sqrt(w2 + x2 + y2 + z2);
		}

		template<typename T>
		template<typename V>
		Vector3<V> Quaternion<T>::rotate(const Vector3<V>& vector) const
		{
			Quaternion<T> vecQuat(vector.x, vector.y, vector.z);

			vecQuat = *this * vecQuat * this->conjugate();

			return{vecQuat.x, vecQuat.y, vecQuat.z};
		}

		template<typename T>
		Quaternion<T> operator+(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
		{
			Quaternion<T> ret;

			ret.w = lhs.w + rhs.w;
			ret.x = lhs.x + rhs.x;
			ret.y = lhs.y + rhs.y;
			ret.z = lhs.z + rhs.z;

			return ret;
		}

		template<typename T>
		Quaternion<T> operator-(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
		{
			Quaternion<T> ret;

			ret.w = lhs.w - rhs.w;
			ret.x = lhs.x - rhs.x;
			ret.y = lhs.y - rhs.y;
			ret.z = lhs.z - rhs.z;

			return ret;
		}

		template<typename T>
		Quaternion<T> operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
		{
			Quaternion<T> ret;

			ret.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
			ret.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
			ret.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
			ret.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;

			return ret;
		}

		template<typename T>
		Quaternion<T> operator*(const Quaternion<T>& quat, T scal)
		{
			return{quat.w * scal, quat.x * scal, quat.y * scal, quat.z * scal};
		}

		template<typename T>
		inline Quaternion<T> operator*(T scal, const Quaternion<T>& quat)
		{
			return quat * scal;
		}

		template<typename T>
		inline Quaternion<T>& operator+=(Quaternion<T>& lhs, const Quaternion<T>& rhs)
		{
			return lhs = lhs + rhs;
		}

		template<typename T>
		inline Quaternion<T>& operator-=(Quaternion<T>& lhs, const Quaternion<T>& rhs)
		{
			return lhs = lhs - rhs;
		}

		template<typename T>
		inline Quaternion<T>& operator*=(Quaternion<T>& lhs, const Quaternion<T>& rhs)
		{
			return lhs = lhs * rhs;
		}

		template<typename T>
		inline Quaternion<T>& operator*=(Quaternion<T>& quat, T scal)
		{
			return quat = quat * scal;
		}
	}
}

#endif
