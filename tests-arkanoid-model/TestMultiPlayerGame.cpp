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

			Racket racket1(math::Point2<float>(0.0f, 500.0f-Racket::OFFSET-Racket::HEIGHT/2));
			Racket racket2(math::Point2<float>(0.0f, 0.0f + Racket::OFFSET + Racket::HEIGHT / 2));
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player1("player1");
			Player player2("player2");

			MultiPlayerGame game(field, ball, racket1, player1, racket2, player2);

			Assert::AreEqual(0u, game.getPlayer1().getScore());
			Assert::AreEqual(0u, game.getPlayer2().getScore());
			game.tick();
			Assert::AreEqual(0u, game.getField().getBrickNumber());
			Assert::AreEqual(1u, game.getPlayer1().getScore());
			Assert::AreEqual(0u, game.getPlayer2().getScore());

		}

		TEST_METHOD(TestBallOwner)
		{
			Field field(400.0f, 400.0f);
			
			Racket racket1(math::Point2<float>(0.0f, 500.0f - Racket::OFFSET - Racket::HEIGHT / 2));
			Racket racket2(math::Point2<float>(0.0f, 0.0f + Racket::OFFSET + Racket::HEIGHT / 2));

			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));

			Player player("player");
			Player player2("player2");

			MultiPlayerGame game(field, ball, racket1, player, racket2, player2);
			Assert::AreEqual(0u, game.getPlayer1().getScore());
			Assert::AreEqual(false, game.isFinished());
			game.tick();
			Assert::AreEqual(true, game.isFinished());

		}

		TEST_METHOD(MoveRacket)
		{
			Field field(400.0f, 400.0f);
			Racket racket(math::Point2<float>(1000.0f, 500.0f - Racket::OFFSET - Racket::HEIGHT / 2));
			Ball ball(math::Point2<float>(100.0f, 20.0f), math::Vector2<float>(0.1f, 0.3f));
			Player player("player");
			Game game(field, ball, racket, player);

			game.tick();

			Assert::AreEqual(racket.getPosition().getX(), field.getWidth() - (racket.WIDTH / 2), 1e-6f);

			racket.position().setX(0);
			game.tick();
			Assert::AreEqual(racket.getPosition().getX(), racket.WIDTH / 2, 1e-6f);

			racket.position().setX(200.0f);
			game.tick();
			Assert::AreEqual(racket.getPosition().getX(), 200.0f, 1e-6f);
		}

		TEST_METHOD(CollisionRacket)
		{
			Field field(400.0f, 400.0f);
			Racket racket(math::Point2<float>(200.0f, 500.0f - Racket::OFFSET - Racket::HEIGHT / 2));
			Ball ball(math::Point2<float>(200.0f, 372.0f), math::Vector2<float>(0.0f, 2.0f));
			Player player("player");
			Game game(field, ball, racket, player);

			game.tick();

			Assert::AreEqual(-2.0f, game.getBall().getVelocity()[1], 1e-6f);
		}

		TEST_METHOD(LostGame)
		{
			Field field(400.0f, 400.0f);
			Racket racket(math::Point2<float>(0.0f, 500.0f - Racket::OFFSET - Racket::HEIGHT / 2));
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