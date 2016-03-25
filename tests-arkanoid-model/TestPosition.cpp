#include "CppUnitTest.h"
#include <arkanoid-model\Position.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
	TEST_CLASS(TestPosition) {
		public:
			TEST_METHOD(constructor) {
				Position p(10, 20);

				Assert::AreEqual(10u, p.getX());
				Assert::AreEqual(20u, p.getY());
			}
	};
}