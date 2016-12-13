#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Game.h>
#include <arkanoid-model\Player.h>
#include <arkanoid-model\Vector2.h>
#include <arkanoid-model\Point2.h>
#include <arkanoid-model\MultiPlayerGame.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{

	TEST_CLASS(TestMultiPlayerGame)
	{
	public:
		TEST_METHOD(BrickDamage)
		{
			Field field(400.0f, 400.0f);
			Brick brick(math::Point2<float>(100.0f, 40.0f), 1);

			field.addBrick(brick);

			Racket racket1(math::Point2<float>(0.0f, 500.0f - Racket::OFFSET - Racket::HEIGHT / 2));
			Racket racket2(math::Point2<float>(0.0f, 0.0f + Racket::OFFSET + Racket::HEIGHT / 2));
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player1("player1");
			Player player2("player2");

			MultiPlayerGame game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket1);
			game.setRacket2(&racket2);
			game.setPlayer(&player1);
			game.setPlayer2(&player2);
			game.setBallOwner(&player2);

			Assert::AreEqual(0u, game.getPlayer()->getScore());
			Assert::AreEqual(0u, game.getPlayer2()->getScore());
			game.tick();
			Assert::AreEqual(0u, game.getField()->getBrickNumber());
			Assert::AreEqual(0u, game.getPlayer()->getScore());
			Assert::AreEqual(1u, game.getPlayer2()->getScore());
		}

		TEST_METHOD(TestBallOwner)
		{
			Field field(400.0f, 400.0f);

			Racket racket1(math::Point2<float>(200.f, 390.f));
			Racket racket2(math::Point2<float>(100.f, 10.f));

			Ball ball(math::Point2<float>(100.0f, racket2.bottom() + Ball::RADIUS + 1.f), math::Vector2<float>(0.0f, -1.f));

			Player player("player");
			Player player2("player2");

			MultiPlayerGame game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket1);
			game.setRacket2(&racket2);
			game.setPlayer(&player);
			game.setPlayer2(&player2);
			game.setBallOwner(&player);

			Assert::AreEqual(true, ball.getOwner() == &player);
			game.tick();
			Assert::AreEqual(true, ball.getOwner() == &player2);
		}

		TEST_METHOD(MoveRacket)
		{
			Field field(400.0f, 400.0f);

			Racket racket1(math::Point2<float>(200.f, 390.f));
			Racket racket2(math::Point2<float>(100.f, 10.f));

			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player("player");
			Player player2("player2");

			MultiPlayerGame game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket1);
			game.setRacket2(&racket2);
			game.setPlayer(&player);
			game.setPlayer2(&player2);
			game.setBallOwner(&player);

			racket2.position().setX(field.getWidth());
			game.tick();
			Assert::AreEqual(racket2.right(), field.getWidth(), 1e-6f);

			racket2.position().setX(0);
			game.tick();
			Assert::AreEqual(racket2.left(), 0.f, 1e-6f);

			racket2.position().setX(200.f);
			game.tick();
			Assert::AreEqual(racket2.getPosition().getX(), 200.f, 1e-6f);
		}

		TEST_METHOD(CollisionRacket)
		{
			Field field(400.0f, 400.0f);

			Racket racket1(math::Point2<float>(200.f, 390.f));
			Racket racket2(math::Point2<float>(100.f, 10.f));

			Ball ball(math::Point2<float>(100.0f, racket2.bottom() + Ball::RADIUS + 2.f), math::Vector2<float>(0.f, -2.f));

			Player player("player");
			Player player2("player2");

			MultiPlayerGame game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket1);
			game.setRacket2(&racket2);
			game.setPlayer(&player);
			game.setPlayer2(&player2);
			game.setBallOwner(&player);

			game.tick();

			Assert::AreEqual(2.f, ball.getVelocity()[1], 1e-6f);
		}

		TEST_METHOD(LostGame)
		{
			Field field(400.0f, 400.0f);

			Racket racket1(math::Point2<float>(200.f, 390.f));
			Racket racket2(math::Point2<float>(100.f, 10.f));

			Ball ball(math::Point2<float>(300.f, Ball::RADIUS + 0.9999f), math::Vector2<float>(1.f, -1.f));

			Player player("player");
			Player player2("player2");

			MultiPlayerGame game;
			game.setField(&field);
			game.setBall(&ball);
			game.setRacket(&racket1);
			game.setRacket2(&racket2);
			game.setPlayer(&player);
			game.setPlayer2(&player2);
			game.setBallOwner(&player);

			field.addBrick(Brick(math::Point2<float>(100.0f, 100.0f), 2u));
			player2.setLives(1);

			Assert::AreEqual(false, game.isFinished());

			game.tick();

			Assert::AreEqual(true, game.isFinished());
		}
	};
}