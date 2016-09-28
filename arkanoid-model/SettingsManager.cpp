#include "SettingsManager.h"

SettingsManager::SettingsManager() : m_language(E_FR)
{

}

SettingsManager::~SettingsManager()
{

}

LanguageEnum SettingsManager::getLanguage() const
{
	return m_language;
}

void SettingsManager::setLanguage(LanguageEnum language)
{
	m_language = language;
}