#include "CppUnitTest.h"
#include <arkanoid-model\Point2.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Brick.h>
#include <list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestField)
	{
		public:
		TEST_METHOD(constructor)
		{
			Field field(100.0f, 220.0f);

			Assert::AreEqual(100.0f, field.getWidth(), 0.0001f);
			Assert::AreEqual(220.0f, field.getHeight(), 0.0001f);
		}

		TEST_METHOD(addBrick)
		{
			Field field(100.0f, 200.0f);
			Brick brick(math::Point2<float>(20.0f, 50.0f), 2);

			bool added = field.addBrick(brick);

			Assert::AreEqual(true, added);
			Assert::AreEqual(1u, field.getBrickNumber());
		}

		TEST_METHOD(addBrickOutside)
		{
			Field field(200.0f, 200.0f);
			Brick brick(math::Point2<float>(10.0f, 25.0f), 2);

			bool added = field.addBrick(brick);

			Assert::AreEqual(added, false);
			Assert::AreEqual(0u, field.getBrickNumber());
		}

		TEST_METHOD(addBrickTwice)
		{
			Field field(200.0f, 200.0f);
			Brick brick(math::Point2<float>(40.0f, 50.0f), 2);

			field.addBrick(brick);
			bool added = field.addBrick(brick);

			Assert::AreEqual(added, false);
			Assert::AreEqual(1u, field.getBrickNumber());
		}

		TEST_METHOD(canFitInside)
		{
			Field field(200.0f, 200.0f);
			Brick bIn(math::Point2<float>(100.0f, 120.0f), 2);
			Brick bOut(math::Point2<float>(300.0f, 120.0f), 2);
			Brick bCross(math::Point2<float>(210.0f, 10.0f), 2);

			Assert::AreEqual(true, field.canFitInside(bIn));
			Assert::AreEqual(false, field.canFitInside(bOut));
			Assert::AreEqual(false, field.canFitInside(bCross));
		}

		TEST_METHOD(getListBricks)
		{
			Field field(200.0f, 200.0f);
			Brick brickA(math::Point2<float>(100.0f, 120.0f), 2);
			Brick brickB(math::Point2<float>(50.0f, 120.0f), 2);
			Brick brickC(math::Point2<float>(21.0f, 10.f), 2);

			field.addBrick(brickA);
			field.addBrick(brickB);
			field.addBrick(brickC);

			std::list<Brick> listBricks = field.getListBricks();

			auto it = listBricks.begin();

			Assert::AreEqual(true, *it++ == brickA);
			Assert::AreEqual(true, *it++ == brickB);
			Assert::AreEqual(true, *it++ == brickC);
		}

		TEST_METHOD(removeBrick)
		{
			Field field(200.0f, 200.0f);
			Brick brickA(math::Point2<float>(100.0f, 120.0f), 2);
			Brick brickB(math::Point2<float>(50.0f, 120.0f), 2);
			Brick brickC(math::Point2<float>(21.0f, 10.f), 2);

			field.addBrick(brickA);
			field.addBrick(brickB);
			field.addBrick(brickC);

			field.removeBrick(brickB);

			std::list<Brick> listBricks = field.getListBricks();

			auto it = listBricks.begin();

			Assert::AreEqual(2u, field.getBrickNumber());
			Assert::AreEqual(true, *it++ == brickA);
			Assert::AreEqual(true, *it++ == brickC);
		}
	};
}