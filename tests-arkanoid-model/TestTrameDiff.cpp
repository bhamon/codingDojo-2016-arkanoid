#include "CppUnitTest.h"
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\TrameDiff.h>
#include <memory>
#include <list>
#include <tuple>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestTrameDiff)
	{
		public:
		TEST_METHOD(serialize)
		{
			//1 int : ID trame, 4 float : balle pos et vitesse, int : nb of brick , 2 int: force et ID des briques (2) 
			const size_t size = sizeof(int) + 4 * sizeof(float) + sizeof(int) + 2 * sizeof(int) + 2 * sizeof(float);
			char buffer[size];
			char bufferOut[size];

			Racket racketPlayer1(math::Point2<float>(0, 70)) ;
			Racket racketPlayer2(math::Point2<float>(60, 70)) ;

			Brick b2(math::Point2<float>(60, 70), 2) ;

			Ball ball(math::Point2<float>(20.0, 50.0), math::Vector2<float>(5.0, 6.0));
			//serialize
			arkanoid::network::Trame::serialize(1, &buffer[0]);
			size_t cpt = sizeof(int);
			arkanoid::network::Trame::serialize(ball.getPosition().getX(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(ball.getPosition().getY(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(ball.getVelocity().getX(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(ball.getVelocity().getY(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(racketPlayer1.getPosition().getX(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(racketPlayer2.getPosition().getX(), &buffer[cpt]);
			cpt += sizeof(float);

			arkanoid::network::Trame::serialize(1, &buffer[cpt]);
			cpt += sizeof(int);
			arkanoid::network::Trame::serialize(1, &buffer[cpt]);
			cpt += sizeof(int);
			arkanoid::network::Trame::serialize(static_cast<int>(b2.getStrength()), &buffer[cpt]);
			cpt += sizeof(int);

			std::list<std::tuple<int, int>> listPairIdStrength;

			listPairIdStrength.push_back(std::make_tuple(1, b2.getStrength()));

			arkanoid::network::TrameDiff trDiff(ball, listPairIdStrength, racketPlayer1, racketPlayer2) ;

			size_t sizeOut = trDiff.serialize(bufferOut) ;

			Assert::AreEqual(size, sizeOut) ;

			int result = memcmp(buffer, bufferOut, sizeOut) ;

			Assert::AreEqual(0, result) ;

		}

	};
}