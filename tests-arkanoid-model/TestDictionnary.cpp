#include "CppUnitTest.h"
#include <arkanoid-model\Dictionnary.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TestDictionnary)
	{
		public:
		TEST_METHOD(translation)
		{
			Dictionnary dict;
			
			dict.addTranslation(Dictionnary::E_PLAYER, LanguageEnum::E_EN, std::string("Player"));
			dict.addTranslation(Dictionnary::E_PLAYER, LanguageEnum::E_FR, std::string("Joueur"));
			dict.addTranslation(Dictionnary::E_LEVEL, LanguageEnum::E_EN, std::string("Level"));
			dict.addTranslation(Dictionnary::E_LEVEL, LanguageEnum::E_FR, std::string("Niveau"));

			dict.setDefaultLanguage(LanguageEnum::E_EN);
			Assert::AreEqual(std::string("Player"), dict.translate(Dictionnary::E_PLAYER));
			Assert::AreEqual(std::string("Level"), dict.translate(Dictionnary::E_LEVEL));

			dict.setDefaultLanguage(LanguageEnum::E_FR);
			Assert::AreEqual(std::string("Joueur"), dict.translate(Dictionnary::E_PLAYER));
			Assert::AreEqual(std::string("Niveau"), dict.translate(Dictionnary::E_LEVEL));

		}
	};
}
