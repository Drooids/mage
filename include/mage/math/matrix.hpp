#pragma once

#include <emmintrin.h>

#include <array>
#include <initializer_list>

namespace Math
{
	template<typename T, size_t R, size_t C>
	class Matrix
	{
		static_assert(R > 0, "R must be a positive, non-zero integer");
		static_assert(C > 0, "C must be a positive, non-zero integer");

	protected:
		std::array<T, R*C> ptr{0};

	public:
		Matrix() = default;
		Matrix(std::initializer_list<T> l)
		{
			size_t n = 0;
			for (T ll : l)
				ptr[n++] = ll;
		}

		Matrix& operator+=(Matrix& rhs)
		{
			for (int n = 0; n < R*C; ++n)
				ptr[n] = ptr[n] + rhs.ptr[n];

			return *this;
		}

		Matrix& operator-=(Matrix& rhs)
		{
			for (int n = 0; n < R*C; ++n)
				ptr[n] = ptr[n] - rhs.ptr[n];

			return *this;
		}

		template<size_t N>
		Matrix<T, R, N> operator*(const Matrix<T, C, N>& m2) const
		{
			Matrix<T, R, N> m3;

			// TODO: naive algorithm, optimize later.
			for (int r = 0; r < R; ++r)
				for (int n = 0; n < N; ++n)
					for (int c = 0; c < C; ++c)
						m3(r,n) += ptr[r * C + c] * m2.ptr[c * m2.cols + n];

			return m3;
		}

		Matrix& operator*=(const T scalar)
		{
			for (int n = 0; n < R*C; ++n)
				ptr[n] = ptr[n] * scalar;

			return *this;
		}

		T& operator()(size_t r, size_t c)
		{
			return ptr[r * C + c];
		}

		/**
		 * \brief Transposes a Matrix.
		 * \param M Matrix to be transposed.
		 * \return Transpose of M.
		 */
		static Matrix<T, C, R> transpose(const Matrix& M)
		{
			Matrix<T, C, R> M2;

			for (int r = 0; r < R; ++r)
				for (int c = 0; c < C; ++c)
					M2.ptr[c * R + r] = M.ptr[r * C + c];

			return M2;
		}

		T* unsafe_ptr() const noexcept
		{
			return ptr;
		}

		static constexpr size_t rows = R;
		static constexpr size_t cols = C;

		// All possible sizes are our friend. We're very inclusive.
		// Matrices are healthy at every size!! #HAES2017
		template<typename TT, size_t RR, size_t CC>
		friend class Matrix;
	};
}
