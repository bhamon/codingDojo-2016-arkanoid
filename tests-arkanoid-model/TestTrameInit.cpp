#include "CppUnitTest.h"
#include <arkanoid-model\Field.h>
#include <arkanoid-model\TrameInit.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestTrameInit)
	{
		public:
		TEST_METHOD(serialize)
		{
			size_t size = 2*sizeof(int) + 2 * sizeof(float) + 4 * sizeof(float) + 2 * sizeof(int) ;
			char *buffer = new char[size];
			char *bufferOut = new char[size];
			Field f(100, 100);
			Brick b1(math::Point2<float>(50, 40), 1) ;
			Brick b2(math::Point2<float>(60, 70), 2) ;
			f.addBrick(b1);
			f.addBrick(b2);

			//serialize
			arkanoid::network::Trame::serialize(0, &buffer[0]);
			size_t cpt = sizeof(int);
			arkanoid::network::Trame::serialize(f.getWidth(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(f.getHeight(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(static_cast<int>(f.getBrickNumber()), &buffer[cpt]);
			cpt += sizeof(int);
			arkanoid::network::Trame::serialize(b1.getPosition().getX(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(b1.getPosition().getY(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(static_cast<int>(b1.getStrength()), &buffer[cpt]);
			cpt += sizeof(int);
			arkanoid::network::Trame::serialize(b2.getPosition().getX(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(b2.getPosition().getY(), &buffer[cpt]);
			cpt += sizeof(float);
			arkanoid::network::Trame::serialize(static_cast<int>(b2.getStrength()), &buffer[cpt]);

			arkanoid::network::TrameInit trInit(f) ;

			size_t sizeOut = trInit.serialize(bufferOut) ;

			Assert::AreEqual(size, sizeOut) ;

			int result = memcmp(buffer, bufferOut, sizeOut) ;

			Assert::AreEqual(0, result) ;

			delete[] buffer ;
			delete[] bufferOut ;
		}

	};
}