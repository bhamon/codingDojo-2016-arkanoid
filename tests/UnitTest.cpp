using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace tests
{
	[TestClass]
	public ref class UnitTest
	{
		private:
			TestContext^ testContextInstance;

		public:
			property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext {
				Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get() {
					return testContextInstance;
				}

				System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value) {
					testContextInstance = value;
				}
			}

			//
			//You can use the following additional attributes as you write your tests:
			//
			//Use ClassInitialize to run code before running the first test in the class
			//[ClassInitialize()]
			//static void MyClassInitialize(TestContext^ testContext) {};
			//
			//Use ClassCleanup to run code after all tests in a class have run
			//[ClassCleanup()]
			//static void MyClassCleanup() {};
			//
			//Use TestInitialize to run code before running each test
			//[TestInitialize()]
			//void MyTestInitialize() {};
			//
			//Use TestCleanup to run code after each test has run
			//[TestCleanup()]
			//void MyTestCleanup() {};
			//

			[TestMethod]
			void TestMethod1()
			{
				//
				// TODO: Add test logic here
				//
			}
	};
}
