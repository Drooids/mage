#include <gtest/gtest.h>

#include <mage/math/matrix.hpp>

TEST(MatrixTest, MatRxCAddition)
{
	Math::Matrix<int, 2, 2> M1 = {
		3, 8,
		4, 6
	};
	Math::Matrix<int, 2, 2> M2 = {
		4,  0,
		1, -9,
	};

	M1 += M2;

	EXPECT_EQ(7,  M1(0,0));
	EXPECT_EQ(8,  M1(0,1));
	EXPECT_EQ(5,  M1(1,0));
	EXPECT_EQ(-3, M1(1,1));
}

TEST(MatrixTest, MatRxCSubtraction)
{
	Math::Matrix<int, 2, 2> M1;
	Math::Matrix<int, 2, 2> M2;

	M1(0, 0) = 3; M1(0, 1) = 8;
	M1(1, 0) = 4; M1(1, 1) = 6;
	M2(0, 0) = 4; M2(0, 1) = 0;
	M2(1, 0) = 1; M2(1, 1) = -9;

	M1 -= M2;

	EXPECT_EQ(-1, M1(0, 0));
	EXPECT_EQ(8, M1(0, 1));
	EXPECT_EQ(3, M1(1, 0));
	EXPECT_EQ(15, M1(1, 1));
}

TEST(MatrixTest, MatRxCMultiplication)
{
	Math::Matrix<int, 2, 3> M1;
	Math::Matrix<int, 3, 2> M2;

	M1(0, 0) = 1; M1(0, 1) = 2; M1(0, 2) = 3;
	M1(1, 0) = 4; M1(1, 1) = 5; M1(1, 2) = 6;

	M2(0, 0) = 7; M2(0, 1) = 8;
	M2(1, 0) = 9; M2(1, 1) = 10;
	M2(2, 0) = 11; M2(2, 1) = 12;

	auto M3 = M1 * M2;

	EXPECT_EQ(58, M3(0, 0));
	EXPECT_EQ(64, M3(0, 1));
	EXPECT_EQ(139, M3(1, 0));
	EXPECT_EQ(154, M3(1, 1));
}

TEST(MatrixTest, MatRxCScalarMultiplication)
{
	Math::Matrix<int, 2, 2> M;
	M(0, 0) = 4; M(0, 1) = 0;
	M(1, 0) = 1; M(1, 1) = -9;
	
	M *= 2;

	EXPECT_EQ(8, M(0, 0));
	EXPECT_EQ(0, M(0, 1));
	EXPECT_EQ(2, M(1, 0));
	EXPECT_EQ(-18, M(1, 1));
}

TEST(MatrixTest, MatRxCTranpose)
{
	Math::Matrix<int, 2, 3> M;
	M(0, 0) = 6; M(0, 1) = 4; M(0, 2) = 24;
	M(1, 0) = 1; M(1, 1) = -9; M(1, 2) = 8;

	auto M2 = Math::Matrix<int, 2, 3>::transpose(M);

	EXPECT_EQ(6, M2(0, 0));
	EXPECT_EQ(1, M2(0, 1));
	EXPECT_EQ(4, M2(1, 0));
	EXPECT_EQ(-9, M2(1, 1));
	EXPECT_EQ(24, M2(2, 0));
	EXPECT_EQ(8, M2(2, 1));
}
