#ifndef ARKANOID_MULTI_PLAYER_GAME_H
#define ARKANOID_MULTI_PLAYER_GAME_H

#include "Game.h"

class MultiPlayerGame : public Game
{

	private:
	Racket &m_racket2;
	Player &m_player2;

	public:
	MultiPlayerGame(Field &field, Ball &ball, Racket &racket1, Player &player1, Racket &racket2, Player &player2);
	~MultiPlayerGame();

	const Racket & getRacket2() const;
	const Player & getPlayer2() const;

	virtual void tick();

	bool isFinished();
};


#endif