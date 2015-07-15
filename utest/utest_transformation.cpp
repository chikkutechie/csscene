
#include <math.h>

#include "rtestsuite.h"
#include "rtransformation.h"
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

TEST(RTransformation, identity)
{
	RTransformation m;

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(MATRIX_IDENTITY[i], m.matrix().data()[i]));
	}
}

TEST(RTransformation, multiplication)
{
	RTransformation m;
	RTransformation m1 = m.multiply(m);

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(MATRIX_IDENTITY[i], m1.matrix().data()[i]));
	}
}


TEST(RTransformation, inverseTranslate)
{
	RTransformation i;
	i.translate(1, 2, 3);

	RTransformation m = i.inverse();

	EXPECT_TRUE(fcompare(-1, m.matrix().data()[12]));
	EXPECT_TRUE(fcompare(-2, m.matrix().data()[13]));
	EXPECT_TRUE(fcompare(-3, m.matrix().data()[14]));
}

TEST(RTransformation, inverseScale)
{
	RTransformation i;
	i.scale(1, 2, 3);

	RTransformation m = i.inverse();

	EXPECT_TRUE(fcompare(1.0f, m.matrix().data()[0]));
	EXPECT_TRUE(fcompare(1.0f/2.0f, m.matrix().data()[5]));
	EXPECT_TRUE(fcompare(1.0f/3.0f, m.matrix().data()[10]));
}

TEST(RTransformation, inverseMultiply)
{
	RTransformation i;
	i.scale(1, 2, 3);
	i.translate(1, 2, 3);
	i.rotate(0, 0, 1, 45);

	RTransformation m = i.inverse();

	m = m.multiply(i);

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(MATRIX_IDENTITY[i], m.matrix().data()[i]));
	}
}

TEST(RTransformation, transpose)
{
	RTransformation i;
	i.translate(1, 2, 3);

	i = i.transpose();

	EXPECT_TRUE(fcompare(1.0f, i.matrix().data()[3]));
	EXPECT_TRUE(fcompare(2.0f, i.matrix().data()[7]));
	EXPECT_TRUE(fcompare(3.0f, i.matrix().data()[11]));
}

TEST(RTransformation, transposeMultiple)
{
	RTransformation o;
	o.scale(1, 2, 3);
	o.translate(1, 2, 3);
	o.rotate(0, 0, 1, 45);

	RTransformation m = o.transpose().transpose();

	for (int i=0; i<16; ++i) {
		EXPECT_TRUE(fcompare(o.matrix().data()[i], m.matrix().data()[i]));
	}
}

TEST(RTransformation, translate)
{
	RTransformation m;

	m.translate(1, 2, 3);

	EXPECT_TRUE(fcompare(1, m.matrix().data()[12]));
	EXPECT_TRUE(fcompare(2, m.matrix().data()[13]));
	EXPECT_TRUE(fcompare(3, m.matrix().data()[14]));
}

TEST(RTransformation, translateMultiple)
{
	RTransformation m;

	m.translate(1, 2, 3);
	m.translate(1, 2, 3);

	EXPECT_TRUE(fcompare(2, m.matrix().data()[12]));
	EXPECT_TRUE(fcompare(4, m.matrix().data()[13]));
	EXPECT_TRUE(fcompare(6, m.matrix().data()[14]));
}

TEST(RTransformation, scale)
{
	RTransformation m;

	m.scale(1, 2, 3);

	EXPECT_TRUE(fcompare(1, m.matrix().data()[0]));
	EXPECT_TRUE(fcompare(2, m.matrix().data()[5]));
	EXPECT_TRUE(fcompare(3, m.matrix().data()[10]));
}

TEST(RTransformation, scaleMultiple)
{
	RTransformation m;

	m.scale(1, 2, 3);
	m.scale(3, 4, 5);

	EXPECT_TRUE(fcompare(3, m.matrix().data()[0]));
	EXPECT_TRUE(fcompare(8, m.matrix().data()[5]));
	EXPECT_TRUE(fcompare(15, m.matrix().data()[10]));
}

int main(int argc, char **argv)
{
    return ExcecuteTests();
}


