#ifndef GAME_H
#define GAME_H

#include "Racket.h"
#include "Ball.h"
#include "Field.h"
#include "Player.h"

class Game
{

	private:

		Racket &m_racket;
		Ball &m_ball;
		Field &m_field;
		Player &m_player;

	public:

	Game(Field &field, Ball &ball, Racket &racket, Player &player);
		~Game();

		void tick();

		const Racket & getRacket() const;
		const Ball & getBall() const;
		const Field & getField() const;
		const Player & getPlayer() const;

		bool isFinished();
};


#endif