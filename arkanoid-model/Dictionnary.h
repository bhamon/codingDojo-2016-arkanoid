#ifndef ARKANOID_DICTIONNARY_H
#define ARKANOID_DICTIONNARY_H

#include <map>
#include "Enum.h"

class Dictionnary
{
	public:

	enum KeyWord
	{
		E_PLAYER = 0,
		E_LEVEL,
		E_RETURN,
		E_QUIT,
		E_LIFE,
		E_PARAMETERS
	};

	Dictionnary();
	~Dictionnary();
	
	void setDefaultLanguage(LanguageEnum lang);
	void addTranslation(KeyWord word, LanguageEnum, const std::string &translation);
	const std::string& translate(KeyWord word) const;

	private:

	typedef std::map<KeyWord, std::map<LanguageEnum, std::string> > TranslationMap;
	TranslationMap m_translationMap;
	LanguageEnum m_lang;
	std::string m_emptyString ;

};

#endif