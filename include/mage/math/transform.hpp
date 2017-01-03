#pragma once

#include <mage/math/matrix.hpp>

namespace Math
{
	template<typename T>
	Matrix<T, 4, 4> ortho(T left, T right, T top, T bottom, T near, T far)
	{
		Matrix<T, 4, 4> M = {
			2 / (right - left), 0, 0, -((right + left) / (right - left)),
			0, 2 / (top - bottom), 0, -((top + bottom) / (top - bottom)),
			0, 0, -(2 / (far - near)), -((far + near) / (far - near)),
			0, 0, 0, 1
		};

		return M;
	}
}