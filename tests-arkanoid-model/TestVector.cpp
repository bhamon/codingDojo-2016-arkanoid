#include "CppUnitTest.h"
#include <arkanoid-model\Vector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestVector)
	{
		public:
		TEST_METHOD(constructor)
		{
			VectorF v(10, -20);

			Assert::AreEqual(10.f, v.getX());
			Assert::AreEqual(-20.f, v.getY());
		}

		TEST_METHOD(setters)
		{
			VectorF v(10, -20);

			v.setX(-42);
			v.setY(98);

			Assert::AreEqual(-42.f, v.getX());
			Assert::AreEqual(98.f, v.getY());
		}

		TEST_METHOD(getNorm)
		{
			VectorF v(4, 3);

			Assert::AreEqual(5.f, v.getNorm());
		}

		TEST_METHOD(normalize)
		{
			VectorF v(2, 3);

			v.normalize();

			Assert::AreEqual(1.f, v.getNorm());
		}

		TEST_METHOD(operators)
		{
			VectorF v(2, 3);
			VectorF v2(4, 5);
			VectorF v3(4, 9);

			VectorF vadd = v + v2;
			VectorF vsub = v - v2;
			VectorF vmul = v * v2;
			VectorF vmuls = v * 2.f;
			VectorF vmulsInv = 2.0f * v;
			VectorF vdiv = v3 / v;
			VectorF vdivs = v3 / 0.5f;


			Assert::AreEqual(6.f, vadd.getX());
			Assert::AreEqual(8.f, vadd.getY());

			Assert::AreEqual(-2.f, vsub.getX());
			Assert::AreEqual(-2.f, vsub.getY());

			Assert::AreEqual(8.f, vmul.getX());
			Assert::AreEqual(15.f, vmul.getY());

			Assert::AreEqual(4.f, vmuls.getX());
			Assert::AreEqual(6.f, vmuls.getY());

			Assert::AreEqual(4.f, vmulsInv.getX());
			Assert::AreEqual(6.f, vmulsInv.getY());

			Assert::AreEqual(2.f, vdiv.getX());
			Assert::AreEqual(3.f, vdiv.getY());

			Assert::AreEqual(8.f, vdivs.getX());
			Assert::AreEqual(18.f, vdivs.getY());
		}

		TEST_METHOD(dot)
		{
			VectorF v(2, 3);
			VectorF v2(4, 6);

			Assert::AreEqual(26.f, v.dot(v2));
		}

		TEST_METHOD(inverse)
		{
			VectorF v(2, 3);
			VectorF v2(0, 0);
			v2 = -v;
			Assert::AreEqual(-2.f, v2.getX());
			Assert::AreEqual(-3.f, v2.getY());

		}
	};
}