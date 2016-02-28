#ifndef DBR_MATH_MATRIX_HPP
#define DBR_MATH_MATRIX_HPP

#include <array>
#include <algorithm>

namespace dbr
{
	namespace math
	{
		template<typename T, std::size_t Cols, std::size_t Rows>
		class Matrix
		{
			friend class Matrix;

			public:
				using Type = T;

				static Matrix<T, Cols, Cols> identity();

				static Matrix<T, Rows, Cols> transpose(const Matrix<T, Cols, Rows>& m);
				
				Matrix() = default;
				Matrix(const std::array<T, Cols * Rows>& arr);
				Matrix(std::array<T, Cols * Rows>&& arr);

				// "row major"
				// ie. for a 4x4 matrix, accessing (3, 0) gives index 3,
				// whereas accessing (0, 3) gives index 12
				T& operator()(std::size_t col, std::size_t row);
				const T& operator()(std::size_t col, std::size_t row) const;

				T& operator[](std::size_t idx);
				const T& operator[](std::size_t idx) const;

				constexpr std::size_t cols() const;
				constexpr std::size_t rows() const;

				// convert element type
				template<typename U>
				operator Matrix<U, Cols, Rows>() const;

				const T* data() const;

				// arithmetic
				template<typename U>
				Matrix<T, Cols, Rows>& operator+=(const Matrix<U, Cols, Rows>& other);

				template<typename U>
				Matrix<T, Cols, Rows>& operator-=(const Matrix<U, Cols, Rows>& other);

				// higher restriction than operator* because we don't change the size of *this
				template<typename U>
				Matrix<T, Cols, Rows>& operator*=(const Matrix<U, Cols, Cols>& other);

				template<typename U, typename = std::enable_if<std::is_fundamental<U>::value>::type>
				Matrix<T, Cols, Rows>& operator*=(const U& scalar);

				template<typename U>
				friend auto operator+(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, Cols, Rows>& rhs);

				template<typename U>
				friend auto operator-(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, Cols, Rows>& rhs);

				template<typename U, std::size_t OtherCols>
				friend auto operator*(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, OtherCols, Cols>& rhs);

				template<typename U, typename = std::enable_if<std::is_fundamental<U>::value>::type>
				friend auto operator*(const Matrix<T, Cols, Rows>& other, const U& scalar);

				template<typename U, typename = std::enable_if<std::is_fundamental<U>::value>::type>
				friend auto operator*(const U& scalar, const Matrix<T, Cols, Rows>& other);

			private:
				std::array<T, Cols * Rows> values;
		};

		template<typename T, std::size_t Cols, std::size_t Rows>
		Matrix<T, Cols, Cols> Matrix<T, Cols, Rows>::identity()
		{
			static_assert(Cols == Rows, "Only square matrices have an identity matrix");

			constexpr auto S = Cols;

			Matrix<T, S, S> ret;

			for(auto i = 0u; i < S; ++i)
				ret(i, i) = 1;

			return ret;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		Matrix<T, Rows, Cols> Matrix<T, Cols, Rows>::transpose(const Matrix<T, Cols, Rows>& m)
		{
			Matrix<T, Rows, Cols> ret;

			for(int i = 0; i < Rows; ++i)
			{
				for(int j = 0; j < Cols; ++j)
				{
					ret(j, i) = m(i, j);
				}
			}

			return ret;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		Matrix<T, Cols, Rows>::Matrix(const std::array<T, Cols * Rows>& arr)
		:	values(arr)
		{}

		template<typename T, std::size_t Cols, std::size_t Rows>
		Matrix<T, Cols, Rows>::Matrix(std::array<T, Cols * Rows>&& arr)
		:	values(std::move(arr))
		{}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline T& Matrix<T, Cols, Rows>::operator()(std::size_t col, std::size_t row)
		{
			return values[col + row * Cols];
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline const T& Matrix<T, Cols, Rows>::operator()(std::size_t col, std::size_t row) const
		{
			return values[col + row * Cols];
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline T& Matrix<T, Cols, Rows>::operator[](std::size_t idx)
		{
			return values[idx];
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline const T& Matrix<T, Cols, Rows>::operator[](std::size_t idx) const
		{
			return values[idx];
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		constexpr std::size_t Matrix<T, Cols, Rows>::cols() const
		{
			return Cols;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		constexpr std::size_t Matrix<T, Cols, Rows>::rows() const
		{
			return Rows;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		Matrix<T, Cols, Rows>::operator Matrix<U, Cols, Rows>() const
		{
			Matrix<U, Cols, Rows> newMatrix;

			auto it = values.begin();
			auto nit = newMatrix.values.begin();

			for(; it != values.end(); ++it, ++nit)
				*nit = static_cast<U>(*it);

			return newMatrix;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline const T * Matrix<T, Cols, Rows>::data() const
		{
			return values.data();
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		inline Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator+=(const Matrix<U, Cols, Rows>& other)
		{
			return *this = *this + other;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		inline Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator-=(const Matrix<U, Cols, Rows>& other)
		{
			return *this = *this - other;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		inline  Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator*=(const Matrix<U, Cols, Cols>& other)
		{
			return *this = *this * other;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U, typename E>
		Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator*=(const U& scalar)
		{
			for(auto& v : values)
				v *= scalar;

			return *this;
		}

		template<typename T, typename U, std::size_t Cols, std::size_t Rows>
		auto operator+(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, Cols, Rows>& rhs)
		{
			using R = decltype(std::declval<T>() + std::declval<U>());

			Matrix<R, Cols, Rows> ret;

			auto lit = lhs.values.begin();
			auto rit = rhs.values.begin();
			auto oit = ret.values.begin();

			for(; lit != lhs.values.end(); ++lit, ++rit, ++oit)
				*oit = *lit + *rit;

			return ret;
		}

		template<typename T, typename U, std::size_t Cols, std::size_t Rows>
		auto operator-(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, Cols, Rows>& rhs)
		{
			using R = decltype(std::declval<T>() + std::declval<U>());

			Matrix<R, Cols, Rows> ret;

			auto lit = lhs.values.begin();
			auto rit = rhs.values.begin();
			auto oit = ret.values.begin();

			for(; lit != lhs.values.end(); ++lit, ++rit, ++oit)
				*oit = *lit - *rit;

			return ret;
		}

		template<typename T, typename U, std::size_t Cols, std::size_t Rows, std::size_t OtherCols>
		auto operator*(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, OtherCols, Cols>& rhs)
		{
			using R = decltype(std::declval<T>() + std::declval<U>());

			Matrix<R, OtherCols, Rows> ret;

			for(auto i = 0u; i < ret.rows(); ++i)
			{
				for(auto j = 0u; j < ret.cols(); ++j)
				{
					for(auto k = 0u; k < Cols; ++k)
					{
						ret(j, i) += lhs(k, i) * rhs(j, k);
					}
				}
			}

			return ret;
		}

		template<typename T, std::size_t Cols, std::size_t Rows, typename U>
		auto operator*(const Matrix<T, Cols, Rows>& matrix, const U& scalar)
		{
			using R = decltype(std::declval<T>() * std::declval<U>());

			Matrix<R, Cols, Rows> out;

			auto mit = matrix.values.begin();
			auto oit = out.values.begin();

			for(; mit != matrix.values.end(); ++mit, ++oit)
				*oit = *mit * scalar;

			return out;
		}

		template<typename T, std::size_t Cols, std::size_t Rows, typename U>
		inline auto operator*(const U& scalar, const Matrix<T, Cols, Rows>& matrix)
		{
			return matrix * scalar;
		}
	}
}

#ifdef DBR_MATH_MATRIX_PRINT

#include <string>
#include <iostream>

namespace dbr
{
	namespace math
	{
		template<typename T, std::size_t Cols, std::size_t Rows>
		void printMatrix(const Matrix<T, Cols, Rows>& mat, const std::string& rowPrefix = "")
		{
			for(int i = 0; i < Rows; ++i)
			{
				std::cout << rowPrefix;

				for(int j = 0; j < Cols; ++j)
				{
					std::cout << mat(j, i) << ' ';
				}

				std::cout << '\n';
			}

			std::cout << '\n';
		}
	}
}

#endif

#endif
