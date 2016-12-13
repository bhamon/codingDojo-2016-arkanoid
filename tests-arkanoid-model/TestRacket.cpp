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
			math::Point2<float> racketPos(10.0f, 400.0f);
			Racket r(racketPos);

			Assert::IsTrue(r.getPosition() == racketPos);
			Assert::AreEqual(r.top(), 392.5f, 1e-6f);
			Assert::AreEqual(r.bottom(), 407.5f, 1e-6f);
			Assert::AreEqual(r.right(), 110.f, 1e-6f);
			Assert::AreEqual(r.left(), -90.f, 1e-6f);
		}

		TEST_METHOD(setters)
		{
			math::Point2<float> racketPos(10.f, 400.f);
			Racket r(racketPos);

			r.position() += math::Point2<float>(251.f, -2.f);

			Assert::AreEqual(261.f, r.getPosition().getX(), 1e-6f);
			Assert::AreEqual(398.f, r.getPosition().getY(), 1e-6f);
		}
	};
}