#include "CppUnitTest.h"
#include <arkanoid-model\Calculator.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Vector.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestCalculator)
	{
		public:
		TEST_METHOD(ballMove)
		{
			Ball ball(Position(5, 5), VectorF(0, 1));
			Calculator::move(ball);
			Assert::AreEqual(6.f, ball.getPosition().getY());
			Assert::AreEqual(5.f, ball.getPosition().getX());
		}

		TEST_METHOD(ballCollision)
		{
			Ball ball(Position(5, 5), VectorF(2, 3));
			VectorF normal(0, -1);

			Calculator::collision(ball, normal);

			Assert::AreEqual(2.f, ball.getVector().getX());
			Assert::AreEqual(-3.f, ball.getVector().getY());
		}

		TEST_METHOD(ballCollision2)
		{
			Ball ball(Position(5, 5), VectorF(0, 2));
			VectorF normal(1, -1);

			normal.normalize();
			Calculator::collision(ball, normal);

			Assert::AreEqual(2.f, ball.getVector().getX(), 0.001f);
			Assert::AreEqual(0.f, ball.getVector().getY(), 0.001f);
		}


	};
}