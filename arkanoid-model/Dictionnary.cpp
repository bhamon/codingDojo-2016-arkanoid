#include "Dictionnary.h"


Dictionnary::Dictionnary() :
m_lang(E_FR)
, m_emptyString()
{
	m_translationMap[E_PLAYER][E_EN] = "Player" ;
	m_translationMap[E_LEVEL][E_EN] = "Level" ;
	m_translationMap[E_RETURN][E_EN] = "Return" ;
	m_translationMap[E_QUIT][E_EN] = "Quit" ;
	m_translationMap[E_LIFE][E_EN] = "Lifes" ;
	m_translationMap[E_PARAMETERS][E_EN] = "Parameters" ;

	m_translationMap[E_PLAYER][E_FR] = "Joueur" ;
	m_translationMap[E_LEVEL][E_FR] = "Niveau" ;
	m_translationMap[E_RETURN][E_FR] = "Retour" ;
	m_translationMap[E_QUIT][E_FR] = "Quitter" ;
	m_translationMap[E_LIFE][E_FR] = "Vies" ;
	m_translationMap[E_PARAMETERS][E_FR] = "Parametres" ;
}

Dictionnary::~Dictionnary()
{

}

void Dictionnary::setDefaultLanguage(LanguageEnum lang)
{
	m_lang = lang;
}

void Dictionnary::addTranslation(KeyWord word, LanguageEnum language, const std::string &translation)
{
	m_translationMap[word][language] = translation;
}

const std::string& Dictionnary::translate(KeyWord word) const
{

	auto Iter = m_translationMap.find(word) ;

	if(Iter !=  m_translationMap.end())
	{
		const auto& Map(Iter->second);
		auto Iter2 = Map.find(m_lang);

		if(Iter2 != Map.end())
		{
			return Iter2->second;
		}
		else
		{
			return m_emptyString;
		}

	}
	else
	{
		return m_emptyString ;
	}
}