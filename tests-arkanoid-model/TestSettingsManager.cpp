#include "CppUnitTest.h"
#include <arkanoid-model\Field.h>
#include <iostream>
#include <sstream>
#include "arkanoid-model\SettingsManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestSettingsManager)
	{
		public:
		TEST_METHOD(constructor)
		{
			SettingsManager settingsMgr;
			Assert::AreEqual(static_cast<int> (LanguageEnum::E_FR), static_cast<int> (settingsMgr.getLanguage()));
		}

		TEST_METHOD(changeLanguage)
		{
			SettingsManager settingsMgr;
			settingsMgr.setLanguage(LanguageEnum::E_EN);
			Assert::AreEqual(static_cast<int> (LanguageEnum::E_EN), static_cast<int> (settingsMgr.getLanguage()));
			settingsMgr.setLanguage(LanguageEnum::E_FR);
			Assert::IsTrue(LanguageEnum::E_FR == settingsMgr.getLanguage());
		}

	};
}