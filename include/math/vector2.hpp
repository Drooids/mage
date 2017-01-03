#pragma once

#include <cmath>

namespace Math
{
	class Vector2f
	{
	public:
		union
		{
			struct
			{
				float ptr[2];
			};
			struct
			{
				float x, y;
			};
		};
		
	
		Vector2f(float x, float y) :
		x(x), y(y)
		{
			// nothing to be done!
		}

		float magnitude() const
		{
			return sqrtf(powf(x, 2) + powf(y, 2));
		}

		float direction() const
		{
			return atan(y / x);
		}

		Vector2f& operator+=(const Vector2f& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2f& operator-=(const Vector2f& v)
		{
			x += -v.x;
			y += -v.y;
			return *this;
		}

		Vector2f& operator*=(int scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2f& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		static float dot(const Vector2f& v1, const Vector2f& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}
	};

	inline Vector2f operator+(const Vector2f& a, const Vector2f& b)
	{
		return Vector2f(a.x + b.x, a.y + b.y);
	}

	inline Vector2f operator-(const Vector2f& a, const Vector2f& b) 
	{
		return Vector2f(a.x + -b.x, a.y + -b.y);
	}

	inline Vector2f operator*(const Vector2f& v, float scalar)
	{
		return Vector2f(v.x * scalar, v.y * scalar);
	}

	inline Vector2f operator*(const Vector2f& v, int scalar)
	{
		return Vector2f(v.x * scalar, v.y * scalar);
	}
}
