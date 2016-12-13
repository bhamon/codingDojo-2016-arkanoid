#include "CppUnitTest.h"
#include <arkanoid-model\Player.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestPlayer)
	{
		public:
		TEST_METHOD(constructor)
		{
			Player p("Antoine");

			Assert::AreEqual(std::string("Antoine"), p.getName());
			Assert::AreEqual(0u, p.getScore());
			Assert::AreEqual(3u, p.getLives());
		}

		TEST_METHOD(setters)
		{
			Player p("Antoine");
			p.setName("Romain");
			p.setScore(10);
			p.setLives(2);

			Assert::AreEqual(std::string("Romain"), p.getName());
			Assert::AreEqual(10u, p.getScore());
			Assert::AreEqual(2u, p.getLives());

			p.score() += 4;
			p.lives() -= 1;

			Assert::AreEqual(14u, p.getScore());
			Assert::AreEqual(1u, p.getLives());
		}

		TEST_METHOD(equality)
		{
			Player p1("titi");
			Player p2("titi");

			Assert::IsTrue(p1 == p2);
		};

		TEST_METHOD(setLives)
		{
			Player player("Roger");
			player.setLives(3);

			Assert::AreEqual(3u, player.getLives());
		};

		TEST_METHOD(lostOneLife)
		{
			Player player("Roger");
			player.setLives(3);
			player.lostOneLife();

			Assert::AreEqual(2u, player.getLives());

			player.setLives(0);
			player.lostOneLife();

			Assert::AreEqual(0u, player.getLives());
		};

		TEST_METHOD(incrementScore)
		{
			Player player("Roger");
			player.setScore(2091);
			player.incrementScore();

			Assert::AreEqual(2092u, player.getScore());
		};
	};
}