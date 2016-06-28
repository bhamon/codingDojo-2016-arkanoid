#include "CppUnitTest.h"
#include <arkanoid-model\Position.h>
#include <arkanoid-model\Brick.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestBrick)
	{
		public:
		TEST_METHOD(defaultConstructor)
		{
			Brick brick;

			Assert::AreEqual(false, brick.isValid());
		}

		TEST_METHOD(constructor)
		{
			Position pos(2, 3);
			Brick brick(pos, 1);

			Assert::AreEqual(2.f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(3.f, brick.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1u, brick.getStrength());
		}

		TEST_METHOD(copyConstructor)
		{
			Position pos(2, 3);
			Brick brick1(pos, 1);
			Brick brick2(brick1);

			Assert::AreEqual(2.f, brick2.getPosition().getX(), 0.0001f);
			Assert::AreEqual(3.f, brick2.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1u, brick2.getStrength());
		}

		TEST_METHOD(setters)
		{
			Position pos(2, 3);
			Brick brick(pos, 1);

			brick.setPosition(Position(5, 47));
			brick.setStrength(3);

			Assert::AreEqual(3u, brick.getStrength());
			Assert::AreEqual(5.f, brick.getPosition().getX(), 0.0001f);
			Assert::AreEqual(47.f, brick.getPosition().getY(), 0.0001f);
		}

		TEST_METHOD(createInvalid)
		{
			Position pos(2, 3);
			Brick brick(pos, 0);

			Assert::AreEqual(false, brick.isValid());
		}
	};
}