#ifndef ARKANOID_MULTI_PLAYER_GAME_H
#define ARKANOID_MULTI_PLAYER_GAME_H

#include "Game.h"

class MultiPlayerGame : public Game
{

private:
	Racket* m_pRacket2;
	Player* m_pPlayer2;

public:
	MultiPlayerGame();
	virtual ~MultiPlayerGame();

	void setRacket2(Racket* pRacket);
	void setPlayer2(Player* pPlayer);
	const Racket* getRacket2() const;
	const Player* getPlayer2() const;

	virtual void tick();
	virtual bool isFinished() const;
};


#endif