#include "CppUnitTest.h"
#include <arkanoid-model\Field.h>
#include <arkanoid-model\FieldLoader.h>
#include <iostream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestFieldLoader)
	{
		public:
		TEST_METHOD(constructor)
		{
			Field field(400.0f, 400.0f);
			std::string fieldstring = "0 1 2 3 0 1 3 2 0 0 0 0\n"
								   	  "0 1 2 3 0 1 3 2 0 0 0 0\n"
									  "0 1 2 3 0 1 3 2 0 0 0 0\n";
			std::istringstream file(fieldstring);
			
			FieldLoader::load(file, field);

			Assert::AreEqual(18u, field.getBrickNumber());
		}
	};
}