#ifndef ARKANOID_CONTROLLER_LANGUAGES_H
#define ARKANOID_CONTROLLER_LANGUAGES_H

#include "Controller.h"
#include "Enum.h"

namespace arkanoid
{

	class ControllerLanguages : public arkanoid::Controller
	{
		private:
		LanguageEnum m_languageItem;

		public:
		ControllerLanguages(MainWindow& p_mainWindow);
		virtual ~ControllerLanguages();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void paintScene() const;
	};
}

#endif
