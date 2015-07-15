
#include <math.h>

#include "rtestsuite.h"
#include "rmatrix.h"
#include "rutils.h"

using namespace chikkooos;

namespace
{
static const float MATRIX_IDENTITY[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
}

TEST(RMatrix, identity)
{
	RMatrix m;

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(MATRIX_IDENTITY[i], m.data()[i]));
	}
}

TEST(RMatrix, multiplication)
{
	RMatrix m;
	RMatrix m1 = m * m;

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(MATRIX_IDENTITY[i], m1.data()[i]));
	}
}


TEST(RMatrix, inverseTranslate)
{
	RMatrix i;
	i.translate(1, 2, 3);

	RMatrix m = i.inverse();

	EXPECT_TRUE(fcompare(-1, m.data()[12]));
	EXPECT_TRUE(fcompare(-2, m.data()[13]));
	EXPECT_TRUE(fcompare(-3, m.data()[14]));
}

TEST(RMatrix, inverseScale)
{
	RMatrix i;
	i.scale(1, 2, 3);

	RMatrix m = i.inverse();

	EXPECT_TRUE(fcompare(1.0f, m.data()[0]));
	EXPECT_TRUE(fcompare(1.0f/2.0f, m.data()[5]));
	EXPECT_TRUE(fcompare(1.0f/3.0f, m.data()[10]));
}

TEST(RMatrix, inverseMultiply)
{
	RMatrix i;
	i.scale(1, 2, 3);
	i.translate(1, 2, 3);
	i.rotate(RVector(0, 0, 1), 45);

	RMatrix m = i.inverse();

	m = m * i;

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(MATRIX_IDENTITY[i], m.data()[i]));
	}
}

TEST(RMatrix, transpose)
{
	RMatrix i;
	i.translate(1, 2, 3);

	i = i.transpose();

	EXPECT_TRUE(fcompare(1.0f, i.data()[3]));
	EXPECT_TRUE(fcompare(2.0f, i.data()[7]));
	EXPECT_TRUE(fcompare(3.0f, i.data()[11]));
}

TEST(RMatrix, transposeMultiple)
{
	RMatrix o;
	o.scale(1, 2, 3);
	o.translate(1, 2, 3);
	o.rotate(RVector(0, 0, 1), 45);

	RMatrix m = o.transpose().transpose();

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(o.data()[i], m.data()[i]));
	}
}

TEST(RMatrix, translate)
{
	RMatrix m;

	m.translate(1, 2, 3);

	EXPECT_TRUE(fcompare(1, m.data()[12]));
	EXPECT_TRUE(fcompare(2, m.data()[13]));
	EXPECT_TRUE(fcompare(3, m.data()[14]));
}

TEST(RMatrix, translateMultiple)
{
	RMatrix m;

	m.translate(1, 2, 3);
	m.translate(1, 2, 3);

	EXPECT_TRUE(fcompare(2, m.data()[12]));
	EXPECT_TRUE(fcompare(4, m.data()[13]));
	EXPECT_TRUE(fcompare(6, m.data()[14]));
}

TEST(RMatrix, scale)
{
	RMatrix m;

	m.scale(1, 2, 3);

	EXPECT_TRUE(fcompare(1, m.data()[0]));
	EXPECT_TRUE(fcompare(2, m.data()[5]));
	EXPECT_TRUE(fcompare(3, m.data()[10]));
}

TEST(RMatrix, scaleMultiple)
{
	RMatrix m;

	m.scale(1, 2, 3);
	m.scale(3, 4, 5);

	EXPECT_TRUE(fcompare(3, m.data()[0]));
	EXPECT_TRUE(fcompare(8, m.data()[5]));
	EXPECT_TRUE(fcompare(15, m.data()[10]));
}

int main(int argc, char **argv)
{
    return ExcecuteTests();
}


