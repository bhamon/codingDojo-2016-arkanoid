#include "CppUnitTest.h"
#include <arkanoid-model\Ball.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestBall)
	{
		public:
		TEST_METHOD(constructor)
		{
			VectorF v(1, 2);
			Position p(101, 10);
			Ball ball(p, v);

			Assert::AreEqual(101.f, ball.getPosition().getX(), 0.00001f);
			Assert::AreEqual(10.f, ball.getPosition().getY(), 0.00001f);
			Assert::AreEqual(1.f, ball.getVector().getX(), 0.00001f);
			Assert::AreEqual(2.f, ball.getVector().getY(), 0.00001f);
		}

		TEST_METHOD(setPosition)
		{
			VectorF v(1, 2);
			Position p(101, 10);
			Ball ball(p, v);

			Position position(102, 50);
			ball.setPosition(position);

			Assert::AreEqual(102.f, ball.getPosition().getX(), 0.00001f);
			Assert::AreEqual(50.f, ball.getPosition().getY(), 0.00001f);
		}

		TEST_METHOD(setVector)
		{
			VectorF v(1, 2);
			Position p(101, 10);
			Ball ball(p, v);

			VectorF vector(102, 50);
			ball.setVector(vector);

			Assert::AreEqual(102.f, ball.getVector().getX(), 0.00001f);
			Assert::AreEqual(50.f, ball.getVector().getY(), 0.00001f);
		}
	};
}