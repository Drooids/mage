#include <gtest/gtest.h>

#include <mage/math/vector2.hpp>

class Vec2Test : public ::testing::Test
{
public:
	Vec2Test() :
	v1(8, 13), v2(26, 7)
	{
		// nothing to be done
	}

protected:
	Math::Vector2f v1;
	Math::Vector2f v2;
};

TEST_F(Vec2Test, Vec2Addition)
{
	auto v3 = v1 + v2;
	EXPECT_EQ(34, v3.x);
	EXPECT_EQ(20, v3.y);
}

TEST_F(Vec2Test, Vec2Subtraction)
{
	auto v3 = v1 - v2;
	EXPECT_EQ(-18, v3.x);
	EXPECT_EQ( 6,  v3.y);
}

TEST_F(Vec2Test, Vec2ScalarMult)
{
	auto v3 = v1 * 3;
	auto v4 = v2 * 6;
	EXPECT_EQ(v3.x, 24);
	EXPECT_EQ(v3.y, 39);
	EXPECT_EQ(v4.x, 156);
	EXPECT_EQ(v4.y, 42);
}

TEST_F(Vec2Test, Vec2Magnitude)
{
	EXPECT_FLOAT_EQ(15.264338f, v1.magnitude());
	EXPECT_FLOAT_EQ(26.925824f, v2.magnitude());
}

TEST_F(Vec2Test, Vec2DotProduct)
{
	auto f = Math::Vector2f::dot(v1, v2);
	EXPECT_EQ(f, 299);
}
