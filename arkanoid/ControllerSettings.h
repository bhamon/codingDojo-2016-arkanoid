#ifndef ARKANOID_CONTROLLER_SETTINGS_H
#define ARKANOID_CONTROLLER_SETTINGS_H

#include "Controller.h"

namespace arkanoid
{
	enum SettingsItem
	{
		E_LANGUAGE = 0,
		E_RETOUR =1
	};

	class ControllerSettings : public arkanoid::Controller
	{
		private:
		SettingsItem m_settingsItem;
		
		public:
		ControllerSettings(MainWindow& p_mainWindow);
		virtual ~ControllerSettings();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void animate();
		virtual void paintScene() const;
	};
}

#endif
