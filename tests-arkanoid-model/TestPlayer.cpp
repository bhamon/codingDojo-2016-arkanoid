#include "CppUnitTest.h"
#include <arkanoid-model\Player.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
	TEST_CLASS(TestPlayer) {
		public:
			TEST_METHOD(constructor) {
				Player p("Antoine");

				Assert::AreEqual(std::string("Antoine"), p.getName());
				Assert::AreEqual(0u, p.getScore());
				Assert::AreEqual(3u, p.getLives());
			}

			TEST_METHOD(setters) {
				Player p("Antoine");
				p.setName("Romain");
				p.setLives(2);
				p.setScore(10);

				Assert::AreEqual(std::string("Romain"), p.getName());
				Assert::AreEqual(2u, p.getLives());
				Assert::AreEqual(10u, p.getScore());
			}
	};
}