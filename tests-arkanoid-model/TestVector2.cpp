#include "CppUnitTest.h"
#include <arkanoid-model\Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestVector2)
	{
		public:
		TEST_METHOD(defaultConstructor)
		{
			math::Vector2<int> v;

			Assert::AreEqual(0, v.getX());
			Assert::AreEqual(0, v.getY());
		}

		TEST_METHOD(constructor)
		{
			math::Vector2<int> v(12, -259);

			Assert::AreEqual(12, v.getX());
			Assert::AreEqual(-259, v.getY());
		}

		TEST_METHOD(copyConstructor)
		{
			math::Vector2<int> v1(-85, 123);
			math::Vector2<int> v2(v1);

			Assert::AreEqual(-85, v2.getX());
			Assert::AreEqual(123, v2.getY());
		}

		TEST_METHOD(affectationOperator)
		{
			math::Vector2<int> v1(-78, -12);
			math::Vector2<int> v2;

			v2 = v1;

			Assert::AreEqual(-78, v2.getX());
			Assert::AreEqual(-12, v2.getY());
		}

		TEST_METHOD(castOperator)
		{
			math::Vector2<float> v1(12.3f, 32.56f);
			math::Vector2<int> v2(v1);

			Assert::AreEqual(12, v2.getX());
			Assert::AreEqual(32, v2.getY());
		}

		TEST_METHOD(rawAccess)
		{
			math::Vector2<int> v(12, 51);

			Assert::AreEqual(12, v.getData()[0]);
			Assert::AreEqual(12, v[0]);
			Assert::AreEqual(51, v.getData()[1]);
			Assert::AreEqual(51, v[1]);

			v.data()[0] = -52;
			v.data()[1] = -8;

			Assert::AreEqual(-52, v.getX());
			Assert::AreEqual(-8, v.getY());
		}

		TEST_METHOD(setters)
		{
			math::Vector2<int> v;

			v.setX(-2);
			v.setY(-4);

			Assert::AreEqual(-2, v.getX());
			Assert::AreEqual(-4, v.getY());

			v.x() = 7;
			v.y() = 9;

			Assert::AreEqual(7, v.getX());
			Assert::AreEqual(9, v.getY());
		}

		TEST_METHOD(addition)
		{
			math::Vector2<int> v1(0, -9);
			math::Vector2<int> v2(12, 9);

			math::Vector2<int> v3(v1 + v2);
			v1 += v2;

			Assert::AreEqual(12, v1.getX());
			Assert::AreEqual(0, v1.getY());

			Assert::AreEqual(12, v3.getX());
			Assert::AreEqual(0, v3.getY());
		}

		TEST_METHOD(subtraction)
		{
			math::Vector2<int> v1(10, -8);
			math::Vector2<int> v2(-1, 2);

			math::Vector2<int> v3(v1 - v2);
			v1 -= v2;

			Assert::AreEqual(11, v1.getX());
			Assert::AreEqual(-10, v1.getY());

			Assert::AreEqual(11, v3.getX());
			Assert::AreEqual(-10, v3.getY());
		}

		TEST_METHOD(multiplication)
		{
			math::Vector2<int> v1(10, -8);

			math::Vector2<int> v2(v1 * 4);
			v1 *= 4;

			Assert::AreEqual(40, v1.getX());
			Assert::AreEqual(-32, v1.getY());

			Assert::AreEqual(40, v2.getX());
			Assert::AreEqual(-32, v2.getY());
		}

		TEST_METHOD(division)
		{
			math::Vector2<int> v1(12, -4);

			math::Vector2<int> v2(v1 / 2);
			v1 /= 2;

			Assert::AreEqual(6, v1.getX());
			Assert::AreEqual(-2, v1.getY());

			Assert::AreEqual(6, v2.getX());
			Assert::AreEqual(-2, v2.getY());
		}

		TEST_METHOD(magnitude)
		{
			math::Vector2<float> v(3.0f, -4.0f);
			Assert::AreEqual(25.0f, v.getSquaredMagnitude(), 0.0001f);
			Assert::AreEqual(5.0f, v.getMagnitude(), 0.0001f);
		}

		TEST_METHOD(normalization)
		{
			math::Vector2<float> v1(3.0f, -4.0f);

			math::Vector2<float> v2(v1.getNormalized());
			v1.normalize();

			Assert::AreEqual(0.6f, v1.getX(), 0.0001f);
			Assert::AreEqual(-0.8f, v1.getY(), 0.0001f);

			Assert::AreEqual(0.6f, v2.getX(), 0.0001f);
			Assert::AreEqual(-0.8f, v2.getY(), 0.0001f);
		}

		TEST_METHOD(inverse)
		{
			math::Vector2<int> v1(3, -4);

			math::Vector2<int> v2(-v1);

			Assert::AreEqual(-3, v2.getX());
			Assert::AreEqual(4, v2.getY());
		}

		TEST_METHOD(dot)
		{
			math::Vector2<int> v1(3, -4);
			math::Vector2<int> v2(-2, -1);

			int dot = v1 * v2;

			Assert::AreEqual(-2, dot);
		}
	};
}