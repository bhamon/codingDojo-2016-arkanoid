#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Player.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestGame)
	{
		public:
		TEST_METHOD(BrickDamage)
		{
			Field field(10, 22);

			Position pos(2, 3);
			Brick brick(pos, 3);

			VectorF v(0, 1);
			Position p(2, 2);
			Ball ball(p, v);

			//	std::list<Brick> reachableBricks = field.getReachableBricks(ball);
		}

	};
}