#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestRacket)
	{
		public:
		TEST_METHOD(constructor)
		{
			Racket r(100);

			Assert::AreEqual(100u, r.getPosition());
		}

		TEST_METHOD(setters)
		{
			Racket r(100);
			r.setPosition(251);

			Assert::AreEqual(251u, r.getPosition());
		}
	};
}