#include "CppUnitTest.h"
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Player.h>
#include <arkanoid-model\Trame.h>

#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestTrame)
	{
		public:
		TEST_METHOD(serialize)
		{
			int id = 88;
			arkanoid::network::Trame tr(id) ;
			char buffer[sizeof(int)];
			size_t size = tr.serialize(buffer);
			Assert::AreEqual(sizeof(int), size);
			int *pn = reinterpret_cast<int*>(buffer);
			Assert::AreEqual(id, *pn);
		}

		TEST_METHOD(serializeInt)
		{
			int i = 3 ;
			char testI[sizeof(int)] ;
			arkanoid::network::Trame::serialize(i, testI) ;
			int * testInt = (int*)testI;
			Assert::IsTrue(i == *testInt) ;
		}

		TEST_METHOD(serializeFloat)
		{
			float i = 7.0f ;
			char testI[sizeof(float)] ;
			arkanoid::network::Trame::serialize(i, testI) ;
			float* testInt = (float*)testI;
			Assert::IsTrue(i == *testInt) ;
		}



	};
}