#ifndef GAME_H
#define GAME_H

#include "Racket.h"
#include "Ball.h"
#include "Field.h"
#include "Player.h"

class Game
{

	protected:

		Racket &m_racket;
		Ball &m_ball;
		Field &m_field;
		Player &m_player;

	public:

	Game(Field &field, Ball &ball, Racket &racket, Player &player);
	virtual ~Game();

		virtual void tick();

		const Racket & getRacket1() const;
		const Ball & getBall() const;
		const Field & getField() const;
		const Player & getPlayer1() const;

		virtual bool isFinished();
};


#endif