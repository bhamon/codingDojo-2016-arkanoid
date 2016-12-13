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

			Racket racket(math::Point2<float>(0.0f, Racket::OFFSET));
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player("player");

			Game game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket);
			game.setPlayer(&player);
			game.setBallOwner(&player);

			Assert::AreEqual(0u, game.getPlayer()->getScore());
			game.tick();
			Assert::AreEqual(0u, game.getField()->getBrickNumber());
			Assert::AreEqual(1u, game.getPlayer()->getScore());
			
		}

		TEST_METHOD(EndGame)
		{
			Field field(400.0f, 400.0f);
			Brick brick(math::Point2<float>(100.0f, 40.0f), 1);

			field.addBrick(brick);

			Racket racket(math::Point2<float>(0.0f, Racket::OFFSET));
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player("player");

			Game game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket);
			game.setPlayer(&player);
			game.setBallOwner(&player);

			Assert::AreEqual(0u, game.getPlayer()->getScore());
			Assert::AreEqual(false, game.isFinished());
			game.tick();
			Assert::AreEqual(true, game.isFinished());

		}

		TEST_METHOD(MoveRacket)
		{
			Field field(400.0f, 400.0f);
			Racket racket(math::Point2<float>(1000.f, Racket::OFFSET));
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));
			Player player("player");
			Game game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket);
			game.setPlayer(&player);
			game.setBallOwner(&player);

			game.tick();

			Assert::AreEqual(racket.right(), field.getWidth(), 1e-6f);

			racket.setPosition(math::Point2<float>(0.f, Racket::OFFSET));
			game.tick();
			Assert::AreEqual(racket.left(), 0.f, 1e-6f);

			racket.setPosition(math::Point2<float>(200.f, Racket::OFFSET));
			game.tick();
			Assert::AreEqual(racket.getPosition().getX(), 200.f, 1e-6f);
		}

		TEST_METHOD(CollisionRacket)
		{
			Field field(400.0f, 400.0f);
			Racket racket(math::Point2<float>(200.0f, 10.f));
			Ball ball(math::Point2<float>(200.0f, racket.bottom() + Ball::RADIUS + 2.f), math::Vector2<float>(0.f, -2.f));
			Player player("player");
			Game game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket);
			game.setPlayer(&player);
			game.setBallOwner(&player);

			game.tick();

			Assert::AreEqual(2.f, ball.getVelocity()[1], 1e-6f);
		}

		TEST_METHOD(LostGame)
		{
			Field field(400.0f, 400.0f);
			Racket racket(math::Point2<float>(0.f, Racket::OFFSET));
			Ball ball(math::Point2<float>(400.0f, 389.0f), math::Vector2<float>(2.0f, 2.0f));
			Player player("player");
			Game game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket);
			game.setPlayer(&player);
			game.setBallOwner(&player);

			field.addBrick(Brick(math::Point2<float>(100.0f, 100.0f), 2u));
			player.setLives(1);
			
			Assert::AreEqual(false, game.isFinished());
			game.tick();

			Assert::AreEqual(true, game.isFinished());
		}

	};
}