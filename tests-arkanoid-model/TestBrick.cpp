#include "CppUnitTest.h"
#include <arkanoid-model\Brick.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestBrick)
	{
		public:
		TEST_METHOD(constructor)
		{
			math::Point2<float> p(2.0f, 3.0f);
			Brick brick(p, 1u);

			Assert::AreEqual(2.0f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(3.0f, brick.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1u, brick.getStrength());
			Assert::AreEqual(true, brick.isValid());
		}

		TEST_METHOD(copyConstructor)
		{
			math::Point2<float> p(2.0f, 3.0f);
			Brick brick1(p, 1u);

			Brick brick2(brick1);

			Assert::AreEqual(2.0f, brick2.getPosition().getX(), 0.0001f);
			Assert::AreEqual(3.0f, brick2.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1u, brick2.getStrength());
			Assert::AreEqual(true, brick2.isValid());
		}

		TEST_METHOD(setPosition)
		{
			math::Point2<float> p1(2.0f, 3.0f);
			Brick brick(p1, 1u);

			math::Point2<float> p2(5.0f, 47.0f);
			brick.setPosition(p2);

			Assert::AreEqual(5.0f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(47.0f, brick.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1u, brick.getStrength());
			Assert::AreEqual(true, brick.isValid());

			math::Point2<float> p3(-9.0f, 1.0f);
			brick.position() = p3;

			Assert::AreEqual(-9.0f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(1.0f, brick.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1u, brick.getStrength());
			Assert::AreEqual(true, brick.isValid());
			Assert::AreEqual(-9.0f - (Brick::WIDTH / 2.f), brick.left(), 1e-6f);
			Assert::AreEqual(-9.0f + (Brick::WIDTH / 2.f), brick.right(), 1e-6f);
			Assert::AreEqual(1.0f - (Brick::HEIGHT / 2.f), brick.top(), 1e-6f);
			Assert::AreEqual(1.0f + (Brick::HEIGHT / 2.f), brick.bottom(), 1e-6f);
		}

		TEST_METHOD(setStrength)
		{
			math::Point2<float> p1(2.0f, 3.0f);
			Brick brick(p1, 1u);

			brick.setStrength(5u);

			Assert::AreEqual(2.0f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(3.0f, brick.getPosition().getY(), 0.0001f);
			Assert::AreEqual(5u, brick.getStrength());
			Assert::AreEqual(true, brick.isValid());

			brick.strength() = 2u;

			Assert::AreEqual(2.0f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(3.0f, brick.getPosition().getY(), 0.0001f);
			Assert::AreEqual(2u, brick.getStrength());
			Assert::AreEqual(true, brick.isValid());
		}

		TEST_METHOD(isValid)
		{
			math::Point2<float> p1(2.0f, 3.0f);
			Brick brick(p1, 0u);

			Assert::AreEqual(false, brick.isValid());

			brick.setStrength(5u);

			Assert::AreEqual(true, brick.isValid());

			brick.setStrength(0u);

			Assert::AreEqual(false, brick.isValid());
		}

		TEST_METHOD(testOverlap)
		{
			Brick bRef(math::Point2<float>(20.0f, 30.0f), 3u);
			Brick bOverlap(math::Point2<float>(25.0f, 32.0f), 3u);
			Brick bNoOverlap(math::Point2<float>(60.0f, 100.0f), 3u);

			Assert::AreEqual(true, bRef.overlap(bOverlap));
			Assert::AreEqual(false, bRef.overlap(bNoOverlap));
		}
	};
}