#include "CppUnitTest.h"
#include <arkanoid-model\Calculator.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\HitRecord.h>
#include <arkanoid-model\Vector2.h>
#include <arkanoid-model\Point2.h>
#include <arkanoid-model\Normal2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestCalculator)
	{
		public:
		TEST_METHOD(move)
		{
			Ball ball(math::Point2<float>(5.0f, 5.0f), math::Vector2<float>(0.0f, 1.0f));

			Calculator::move(ball, 1.0f);

			Assert::AreEqual(5.0f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(6.0f, ball.getPosition().getY(), 0.0001f);
			Assert::AreEqual(0.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(1.0f, ball.getVelocity().getY(), 0.0001f);
		}

		TEST_METHOD(partialMove)
		{
			Ball ball(math::Point2<float>(5.0f, 5.0f), math::Vector2<float>(1.0f, 0.0f));

			Calculator::move(ball, 0.5f);

			Assert::AreEqual(5.5f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(5.0f, ball.getPosition().getY(), 0.0001f);
			Assert::AreEqual(1.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(0.0f, ball.getVelocity().getY(), 0.0001f);
		}

		TEST_METHOD(ballBounceVertical)
		{
			Ball ball(math::Point2<float>(5.0f, 5.0f), math::Vector2<float>(2.0f, 3.0f));
			math::Vector2<float> normal(0.0f, -1.0f);

			Calculator::bounce(ball, normal);

			Assert::AreEqual(5.0f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(5.0f, ball.getPosition().getY(), 0.0001f);
			Assert::AreEqual(2.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(-3.0f, ball.getVelocity().getY(), 0.0001f);
		}

		TEST_METHOD(ballBounceAngle)
		{
			Ball ball(math::Point2<float>(5.0f, 5.0f), math::Vector2<float>(0.0f, 2.0f));
			math::Vector2<float> normal(1.0f, -1.0f);
			normal.normalize();

			Calculator::bounce(ball, normal);

			Assert::AreEqual(5.0f, ball.getPosition().getX(), 0.0001f);
			Assert::AreEqual(5.0f, ball.getPosition().getY(), 0.0001f);
			Assert::AreEqual(2.0f, ball.getVelocity().getX(), 0.0001f);
			Assert::AreEqual(0.0f, ball.getVelocity().getY(), 0.0001f);
		}

		TEST_METHOD(lineLineParallel)
		{
			math::Point2<float> intersection;
			bool hit = Calculator::computeLineLineIntersection(
				math::Point2<float>(1.0f, 4.0f),
				math::Point2<float>(5.0f, 3.0f),
				math::Point2<float>(-2.0f, -3.0f),
				math::Point2<float>(2.0f, -4.0f),
				intersection
			);

			Assert::AreEqual(false, hit);
		}

		TEST_METHOD(lineLineIntersection)
		{
			math::Point2<float> intersection;
			bool hit = Calculator::computeLineLineIntersection(
				math::Point2<float>(0.0f, 0.0f),
				math::Point2<float>(4.0f, -2.0f),
				math::Point2<float>(3.0f, 0.0f),
				math::Point2<float>(1.0f, -2.0f),
				intersection
			);

			Assert::AreEqual(true, hit);
			Assert::AreEqual(2.0f, intersection.getX(), 0.0001f);
			Assert::AreEqual(-1.0f, intersection.getY(), 0.0001f);
		}

		TEST_METHOD(circleSegmentNoIntersection)
		{
			std::tuple<math::Point2<float>, math::Point2<float>> intersections;
			bool hit = Calculator::computeCircleSegmentIntersection(
				math::Point2<float>(3.0f, -1.0f),
				2.0f,
				math::Point2<float>(4.0f, 5.0f),
				math::Point2<float>(5.0f, 6.0f),
				intersections
			);

			Assert::AreEqual(false, hit);
		}

		TEST_METHOD(circleSegmentIntersection)
		{
			std::tuple<math::Point2<float>, math::Point2<float>> intersections;
			bool hit = Calculator::computeCircleSegmentIntersection(
				math::Point2<float>(3.0f, -1.0f),
				2.0f,
				math::Point2<float>(3.0f, 5.0f),
				math::Point2<float>(3.0f, -10.0f),
				intersections
				);

			Assert::AreEqual(true, hit);
			Assert::AreEqual(3.0f, std::get<0>(intersections).getX(), 0.0001f);
			Assert::AreEqual(1.0f, std::get<0>(intersections).getY(), 0.0001f);
			Assert::AreEqual(3.0f, std::get<1>(intersections).getX(), 0.0001f);
			Assert::AreEqual(-3.0f, std::get<1>(intersections).getY(), 0.0001f);
		}

		TEST_METHOD(circleSegmentUpperIntersection)
		{
			std::tuple<math::Point2<float>, math::Point2<float>> intersections;
			bool hit = Calculator::computeCircleSegmentIntersection(
				math::Point2<float>(3.0f, -1.0f),
				2.0f,
				math::Point2<float>(3.0f, 0.0f),
				math::Point2<float>(3.0f, -10.0f),
				intersections
				);

			Assert::AreEqual(true, hit);
			Assert::AreEqual(3.0f, std::get<0>(intersections).getX(), 0.0001f);
			Assert::AreEqual(1.0f, std::get<0>(intersections).getY(), 0.0001f);
			Assert::AreEqual(3.0f, std::get<1>(intersections).getX(), 0.0001f);
			Assert::AreEqual(-3.0f, std::get<1>(intersections).getY(), 0.0001f);
		}

		TEST_METHOD(circleSegmentLowerIntersection)
		{
			std::tuple<math::Point2<float>, math::Point2<float>> intersections;
			bool hit = Calculator::computeCircleSegmentIntersection(
				math::Point2<float>(3.0f, -1.0f),
				2.0f,
				math::Point2<float>(3.0f, 5.0f),
				math::Point2<float>(3.0f, -2.0f),
				intersections
				);

			Assert::AreEqual(true, hit);
			Assert::AreEqual(3.0f, std::get<0>(intersections).getX(), 0.0001f);
			Assert::AreEqual(1.0f, std::get<0>(intersections).getY(), 0.0001f);
			Assert::AreEqual(3.0f, std::get<1>(intersections).getX(), 0.0001f);
			Assert::AreEqual(-3.0f, std::get<1>(intersections).getY(), 0.0001f);
		}

		TEST_METHOD(hitBrick)
		{
			Ball ball(math::Point2<float>(80.0f, 25.0f), math::Vector2<float>(10.0f, 10.0f));
			Brick brick(math::Point2<float>(100.0f, 40.0f), 5u);
			HitRecord hr;

			bool hit = Calculator::hit(ball, brick, hr);

			Assert::AreEqual(true, hit);
		}

		TEST_METHOD(hitSegment)
		{
			Ball ball(math::Point2<float>(20.0f, 60.0f), math::Vector2<float>(10.0f, 10.0f));
			HitRecord hr;

			math::Point2<float> center(20.0f, 65.0f);
			bool hit = Calculator::hit(ball, center + math::Vector2<float>(-20.0f, 0.0f), center + math::Vector2<float>(20.0f, 0.0f), hr);

			Assert::AreEqual(true, hit);
		}
	};
}