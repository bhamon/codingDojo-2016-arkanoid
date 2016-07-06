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
			math::Point2<float> p(101.0f, 10.0f);
			math::Vector2<float> v(1.0f, 2.0f);
			Ball ball(p, v);

			Assert::AreEqual(101.0f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(10.0f, ball.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(2.0f, ball.getVelocity().getY(), 0.0001f);
		}

		TEST_METHOD(copyConstructor)
		{
			math::Point2<float> p(-9.0f, 5.0f);
			math::Vector2<float> v(3.0f, -5.0f);
			Ball ball1(p, v);

			Ball ball2(ball1);

			Assert::AreEqual(-9.0f, ball2.getPosition().getX(), 0.0001f);
			Assert::AreEqual(5.0f, ball2.getPosition().getY(), 0.0001f);
			Assert::AreEqual(3.0f, ball2.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(-5.0f, ball2.getVelocity().getY(), 0.0001f);
		}

		TEST_METHOD(setPosition)
		{
			math::Point2<float> p1(101.0f, 10.0f);
			math::Vector2<float> v(1.0f, 2.0f);
			Ball ball(p1, v);

			math::Point2<float> p2(102.0f, 50.0f);
			ball.setPosition(p2);

			Assert::AreEqual(102.0f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(50.0f, ball.getPosition().getY(), 0.0001f);

			math::Point2<float> p3(12.0f, -5.0f);
			ball.position() = p3;

			Assert::AreEqual(12.0f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(-5.0f, ball.getPosition().getY(), 0.0001f);
		}

		TEST_METHOD(setVelocity)
		{
			math::Point2<float> p(101.0f, 10.0f);
			math::Vector2<float> v1(1.0f, 2.0f);
			Ball ball(p, v1);

			math::Vector2<float> v2(102.0f, 50.0f);
			ball.setVelocity(v2);

			Assert::AreEqual(102.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(50.0f, ball.getVelocity().getY(), 0.0001f);

			math::Vector2<float> v3(-4.0f, 8.0f);
			ball.velocity() = v3;

			Assert::AreEqual(-4.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(8.0f, ball.getVelocity().getY(), 0.0001f);
		}
	};
}