#ifndef ARKANOID_CONTROLLER_MULTI_GAME_H
#define ARKANOID_CONTROLLER_MULTI_GAME_H

#include "ControllerGame.h"

class MultiPlayerGame;

namespace arkanoid
{
	class ControllerMultiGame : public ControllerGame
	{
	public:
		ControllerMultiGame(MainWindow& p_mainWindow, std::istream& file);
		virtual ~ControllerMultiGame();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void animate();
		virtual void paintScene() const;
		
	private:
		MultiPlayerGame* getGame();

		Player m_player2;
		Racket m_racket2;
		bool m_goLeft2;
		bool m_goRight2;
	};
}

#endif // !ARKANOID_CONTROLLER_MULTI_GAME_H
