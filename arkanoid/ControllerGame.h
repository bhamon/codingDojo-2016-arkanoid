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
		Game* m_pGame;
		bool m_goLeft;
		bool m_goRight;

	public:
		ControllerGame(MainWindow& p_mainWindow, std::istream& file);
		ControllerGame(MainWindow& p_mainWindow, std::istream& file, Game* pGame);
		virtual ~ControllerGame();

		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
		virtual void animate();
		virtual void paintScene() const;

	protected:
		Game* getGame();

		void drawBrick(const Brick& brick) const;
		void drawRacket(const Racket& racket) const;

		bool gameIsFinished() const;
		bool ballHasStopped() const;
		void setBallVelocity(const math::Vector2<float>& velocity);
	};
}

#endif
