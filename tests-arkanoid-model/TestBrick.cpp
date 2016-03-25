#include "CppUnitTest.h"
#include <arkanoid-model\Position.h>
#include <arkanoid-model\Brick.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
	TEST_CLASS(TestBrick) {
		public:
			TEST_METHOD(constructor) {
				Position pos(2, 3);
				Brick brick(pos, 1);

				Assert::AreEqual(2u, brick.getPosition().getX());
				Assert::AreEqual(3u, brick.getPosition().getY());
				Assert::AreEqual(1u, brick.getStrength());
			}

			TEST_METHOD(copyConstructor) {
				Position pos(2, 3);
				Brick brick1(pos, 1);
				Brick brick2(brick1);

				Assert::AreEqual(2u, brick2.getPosition().getX());
				Assert::AreEqual(3u, brick2.getPosition().getY());
				Assert::AreEqual(1u, brick2.getStrength());
			}

			TEST_METHOD(setters) {
				Position pos(2, 3);
				Brick brick(pos, 1);

				brick.setStrength(3);

				Assert::AreEqual(3u, brick.getStrength());
			}
	};
}