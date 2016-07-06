#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Game.h>
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
			Field field(400.0f, 400.0f);
			Brick brick(math::Point2<float>(100.0f, 40.0f), 1);

			field.addBrick(brick);

			Racket racket(0.0f);
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player("player");

			Game game(field, ball, racket, player);
			Assert::AreEqual(0u, game.getPlayer().getScore());
			game.tick();
			Assert::AreEqual(0u, game.getField().getBrickNumber());
			Assert::AreEqual(1u, game.getPlayer().getScore());
			
		}

		TEST_METHOD(EndGame)
		{
			Field field(400.0f, 400.0f);
			Brick brick(math::Point2<float>(100.0f, 40.0f), 1);

			field.addBrick(brick);

			Racket racket(0.0f);
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player("player");

			Game game(field, ball, racket, player);
			Assert::AreEqual(0u, game.getPlayer().getScore());
			Assert::AreEqual(false, game.isFinished());
			game.tick();
			Assert::AreEqual(true, game.isFinished());

		}

		TEST_METHOD(MoveRacket)
		{
			Field field(400.0f, 400.0f);
			Racket racket(1000.0f);
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));
			Player player("player");
			Game game(field, ball, racket, player);

			game.tick();

			Assert::AreEqual(racket.getPosition(), field.getWidth()-(racket.WIDTH/2), 1e-6f);

			racket.setPosition(0);
			game.tick();
			Assert::AreEqual(racket.getPosition(), racket.WIDTH / 2, 1e-6f);

			racket.setPosition(200.0f);
			game.tick();
			Assert::AreEqual(racket.getPosition(), 200.0f, 1e-6f);
		}

		TEST_METHOD(CollisionRacket)
		{
			Field field(400.0f, 400.0f);
			Racket racket(200.0f);
			Ball ball(math::Point2<float>(200.0f, 372.0f), math::Vector2<float>(0.0f, 2.0f));
			Player player("player");
			Game game(field, ball, racket, player);

			game.tick();

			Assert::AreEqual(-2.0f,game.getBall().getVelocity()[1], 1e-6f);
		}

		TEST_METHOD(LostGame)
		{
			Field field(400.0f, 400.0f);
			Racket racket(0.0f);
			Ball ball(math::Point2<float>(400.0f, 389.0f), math::Vector2<float>(2.0f, 2.0f));
			Player player("player");
			Game game(field, ball, racket, player);

			field.addBrick(Brick(math::Point2<float>(100.0f, 100.0f), 2u));
			player.setLives(1);
			
			Assert::AreEqual(false, game.isFinished());
			game.tick();

			Assert::AreEqual(true, game.isFinished());
		}

	};
}