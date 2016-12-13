#ifndef ARKANOID_CONTROLLER_LEVEL_H
#define ARKANOID_CONTROLLER_LEVEL_H

#include "Controller.h"

namespace arkanoid
{
	enum LevelItem
	{
		LEVEL_1 = 0,
		LEVEL_2 = 1,
		RETOUR = 2
	};

	class ControllerLevel : public arkanoid::Controller
	{
	private:
		LevelItem m_level;
		bool m_multi;

	public:
		ControllerLevel(MainWindow& p_mainWindow, bool multi = false);
		virtual ~ControllerLevel();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void animate();
		virtual void paintScene() const;
	};
}

#endif
