#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\TrameClientAction.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestTrameClientAction)
	{
		public:
		TEST_METHOD(serialize)
		{
			const size_t size = sizeof(int) + sizeof(float);
			char buffer[size];
			char bufferOut[size];

			Racket racketPlayer(math::Point2<float>(0, 32)) ;

			//serialize
			arkanoid::network::Trame::serialize(2, &buffer[0]);
			size_t cpt = sizeof(int);
			arkanoid::network::Trame::serialize(racketPlayer.getPosition().getX(), &buffer[cpt]);
			cpt += sizeof(float);
			
			arkanoid::network::TrameClientAction trClient(racketPlayer.getPosition().getX());

			size_t sizeOut = trClient.serialize(bufferOut) ;
			Assert::AreEqual(size, sizeOut) ;

			int result = memcmp(buffer, bufferOut, sizeOut) ;
			Assert::AreEqual(0, result) ;
		}

		TEST_METHOD(deserialize)
		{
			const size_t size = sizeof(int) + sizeof(float);
			char bufferOut[size];

			Racket racketPlayer(math::Point2<float>(0, 32)) ;
			arkanoid::network::TrameClientAction trClient(racketPlayer.getPosition().getX());

			trClient.serialize(bufferOut);
			arkanoid::network::TrameClientAction* trClientOut = arkanoid::network::TrameClientAction::deserialize(bufferOut + sizeof(int));

			Assert::IsNotNull(trClientOut);

			Assert::AreEqual(trClientOut->getRacketX(), racketPlayer.getPosition().getX());
		}

	};
}