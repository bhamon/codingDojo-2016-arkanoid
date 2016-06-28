#include "CppUnitTest.h"
#include <arkanoid-model\Position.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Brick.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestField)
	{
		public:
		TEST_METHOD(constructor)
		{
			Field field(10, 22);

			Assert::AreEqual(10u, field.getWidth());
			Assert::AreEqual(22u, field.getHeight());
		}

		public:
		TEST_METHOD(setter)
		{
			Field field;

			field.setWidth(12u);
			field.setHeight(16u);

			Assert::AreEqual(12u, field.getWidth());
			Assert::AreEqual(16u, field.getHeight());
		}

		public:
		TEST_METHOD(addBrick)
		{
			Field field;
			Brick brick(Position(2, 5), 2);

			field.addBrick(brick);
			Assert::AreEqual(1u, field.getBrickNumber());
		}

		public:
		TEST_METHOD(getBrick)
		{
			Field field;
			Brick brick(Position(2, 7), 9);
			Brick brick_test = field.getBrick(Position(2, 7));
			Assert::AreEqual(brick_test.isValid(), false);

			field.addBrick(brick);
			brick_test = field.getBrick(Position(2, 7));
			Assert::AreEqual(brick_test.isValid(), true);


		}


		public:
		TEST_METHOD(addWrongBrick)
		{
			Field field(20, 20);
			Brick brick(Position(10, 25), 2);

			bool hasBeenAdded = field.addBrick(brick);
			Assert::AreEqual(hasBeenAdded, false);

			brick.setPosition(Position(10, 12));
			brick.setStrength(0);
			hasBeenAdded = field.addBrick(brick);
			Assert::AreEqual(hasBeenAdded, false);
		}

		public:
		TEST_METHOD(addBrickTwice)
		{
			Field field(20, 20);
			Brick brick(Position(10, 12), 2);

			bool hasBeenAdded = field.addBrick(brick);
			Assert::AreEqual(hasBeenAdded, true);

			hasBeenAdded = field.addBrick(brick);
			Assert::AreEqual(hasBeenAdded, false);
		}
	};
}