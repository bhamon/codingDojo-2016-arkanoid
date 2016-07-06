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
			Racket r(10.0f);

			Assert::AreEqual(10.0f, r.getPosition(), 0.0001f);
		}

		TEST_METHOD(setters)
		{
			Racket r(100.0f);

			r.setPosition(251.0f);

			Assert::AreEqual(251.0f, r.getPosition(), 0.0001f);

			r.position() += 10.0f;

			Assert::AreEqual(261.0f, r.getPosition(), 0.0001f);
		}
	};
}