#ifndef DBR_MATH_QUATERNION_HPP
#define DBR_MATH_QUATERNION_HPP

#include <cmath>

namespace dbr
{
	namespace math
	{
		template<typename T>
		class Quaternion
		{
			public:
				Quaternion();
				Quaternion(T w, T x, T y, T z);

				Quaternion conjugate() const;
				Quaternion normal() const;
				T norm() const;

				friend Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
				friend Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
				friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
				friend Quaternion operator*(const Quaternion& quat, T scal);

			private:
				T w;
				T x;
				T y;
				T z;
		};

		using Quaternionf = Quaternion<float>;
		using Quaterniond = Quaternion<double>;

		template<typename T>
		Quaternion<T>::Quaternion()
		:	w(1),
			x(0),
			y(0),
			z(0)
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

		}
	}
}

#endif
