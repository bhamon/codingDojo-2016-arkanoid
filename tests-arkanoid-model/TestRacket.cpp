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
			Ball ball(101, 10, 5);

			Assert::AreEqual(101u, ball.getPositionX());
			Assert::AreEqual(10u, ball.getPositionY());
			Assert::AreEqual(5u, ball.getSpeed());
		}
	};
}