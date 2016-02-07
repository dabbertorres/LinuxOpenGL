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

				template<std::size_t S = Cols>
				static Matrix<T, S, S> identity();

				static Matrix<T, Rows, Cols> transpose(const Matrix<T, Cols, Rows>& m);
				
				Matrix() = default;
				Matrix(std::array<T, Cols * Rows> arr);

				// "column major"
				// ie. for a 4x4 matrix, accessing (3, 0) gives index 12
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

				// higher restriction than operator* because we can't change the size of *this
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
		template<std::size_t S>
		Matrix<T, S, S> Matrix<T, Cols, Rows>::identity()
		{
			static_assert(Cols == Rows, "Only square matrices have an identity matrix");

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
					ret(i, j) = m(j, i);
				}
			}

			return ret;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		Matrix<T, Cols, Rows>::Matrix(std::array<T, Cols * Rows> arr)
		:	values(arr)
		{}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline T& Matrix<T, Cols, Rows>::operator()(std::size_t col, std::size_t row)
		{
			return values[row + col * Rows];
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline const T& Matrix<T, Cols, Rows>::operator()(std::size_t col, std::size_t row) const
		{
			return values[row + col * Cols];
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

			std::transform(values.begin(), values.end(), newMatrix.values.begin(), [](const T& in)
			{
				return static_cast<U>(in);
			});

			return newMatrix;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		inline const T * Matrix<T, Cols, Rows>::data() const
		{
			return values.data();
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator+=(const Matrix<U, Cols, Rows>& other)
		{
			auto it = values.begin();
			auto oit = other.values.begin();

			for(; it != values.end(); ++it, ++oit)
				*it = static_cast<T>(*it + *oit);

			return *this;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator-=(const Matrix<U, Cols, Rows>& other)
		{
			auto it = values.begin();
			auto oit = other.values.begin();

			for(; it != values.end(); ++it, ++oit)
				*it = static_cast<T>(*it - *oit);

			return *this;
		}

		template<typename T, std::size_t Cols, std::size_t Rows>
		template<typename U>
		Matrix<T, Cols, Rows>& Matrix<T, Cols, Rows>::operator*=(const Matrix<U, Cols, Cols>& other)
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

			std::transform(lhs.values.begin(), lhs.values.end(), rhs.values.begin(), ret.values.begin(), [](const T& l, const U& r)
			{
				return l + r;
			});

			return ret;
		}

		template<typename T, typename U, std::size_t Cols, std::size_t Rows>
		auto operator-(const Matrix<T, Cols, Rows>& lhs, const Matrix<U, Cols, Rows>& rhs)
		{
			using R = decltype(std::declval<T>() + std::declval<U>());

			Matrix<R, Cols, Rows> ret;

			std::transform(lhs.values.begin(), lhs.values.end(), rhs.values.begin(), ret.values.begin(), [](const T& l, const U& r)
			{
				return l - r;
			});

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

			Matrix<R, Cols, Rows> ret;

			std::transform(matrix.values.begin(), matrix.values.end(), ret.values.begin(), [](const T& t)
			{
				return t * scalar;
			});

			return ret;
		}

		template<typename T, std::size_t Cols, std::size_t Rows, typename U>
		auto operator*(const U& scalar, const Matrix<T, Cols, Rows>& matrix)
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
