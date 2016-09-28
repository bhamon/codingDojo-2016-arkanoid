#include "CppUnitTest.h"
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\Point2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestRacket)
	{
		public:
		TEST_METHOD(constructor)
		{
			math::Point2<float> racketPos(10.0f, 400.0f - Racket::OFFSET);
			Racket r(racketPos);

			Assert::IsTrue(r.getPosition() == racketPos);
		}

		TEST_METHOD(setters)
		{
			math::Point2<float> racketPos(10.0f, 400.0f - Racket::OFFSET);
			Racket r(racketPos);

			r.position() += math::Point2<float>(10.0f, 0.0f);

			Assert::AreEqual(261.0f, r.getPosition().getX(), 0.0001f);
		}
	};
}