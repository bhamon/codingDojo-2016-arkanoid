#ifndef ARKANOID_CONTROLLER_MENU_H
#define ARKANOID_CONTROLLER_MENU_H

#include "Controller.h"

namespace arkanoid
{
	enum MenuItem
	{
		ONE_PLAYER = 0,
		TWO_PLAYERS = 1,
		SETTINGS = 2,
		QUIT = 3
	};

	class ControllerMenu : public arkanoid::Controller
	{
		private:
		MenuItem m_item;

		public:
		ControllerMenu(MainWindow& p_mainWindow);
		virtual ~ControllerMenu();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void animate();
		virtual void paintScene() const;
	};
}

#endif
