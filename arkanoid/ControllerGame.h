#ifndef ARKANOID_CONTROLLER_GAME_H
#define ARKANOID_CONTROLLER_GAME_H

#include "Controller.h"
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Racket.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Player.h>
#include <arkanoid-model\Game.h>

namespace arkanoid
{
	class ControllerGame : public arkanoid::Controller
	{
		private:
		Ball m_ball;
		Racket m_racket;
		Field m_field;
		Player m_player;
		Game m_game;
		bool m_goLeft;
		bool m_goRight;

		public:
		ControllerGame(MainWindow& p_mainWindow, std::istream& file);
		virtual ~ControllerGame();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void animate();
		virtual void paintScene() const;
	};
}

#endif
