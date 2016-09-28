#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "Enum.h"

class SettingsManager
{
	public:

	//Constructor
	SettingsManager();
	//Destructor
	~SettingsManager();
	
	//Accessors
	LanguageEnum getLanguage() const;
	void setLanguage(LanguageEnum language);
	//load et save

	private:
	LanguageEnum m_language;
};

#endif