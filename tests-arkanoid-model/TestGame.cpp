#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Player.h>
#include <arkanoid-model\Vector2.h>
#include <arkanoid-model\Point2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestGame)
	{
		public:
		TEST_METHOD(BrickDamage)
		{
			Field field(10.0f, 22.0f);
			Brick brick(math::Point2<float>(2.0f, 3.0f), 3);

			Ball ball(math::Point2<float>(0.0f, 1.0f), math::Vector2<float>(2.0f, 2.0f));

			//	std::list<Brick> reachableBricks = field.getReachableBricks(ball);
		}

	};
}