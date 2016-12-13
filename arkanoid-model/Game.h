#ifndef GAME_H
#define GAME_H

#include "Racket.h"
#include "Ball.h"
#include "Field.h"
#include "Player.h"

class HitRecord;

class Game
{
private:

	Racket* m_pRacket;
	Ball* m_pBall;
	Field* m_pField;
	Player* m_pPlayer;

public:
	Game();
	virtual ~Game();

	void setRacket(Racket* pRacket);
	void setBall(Ball* pBall);
	void setField(Field* pField);
	void setPlayer(Player* pPlayer);
	const Racket* getRacket() const;
	const Ball* getBall() const;
	const Field* getField() const;
	const Player* getPlayer() const;

	void setBallOwner(const Player* pPlayer);

	virtual void tick();
	virtual bool isFinished() const;

protected:
	void ballMove();
	void forceRacketIntoField(Racket* pRacket);
	void forceRacketIntoField();
	bool hitTopField(HitRecord& lhr) const;
	bool hitBottomField(HitRecord& lhr) const;
	bool hitLeftField(HitRecord& lhr) const;
	bool hitRightField(HitRecord& lhr) const;
	void hitRacket(const Player* pPlayer, const Racket* racket, HitRecord& lhr, HitRecord& hr, bool& hit);
	void hitRacket(HitRecord& lhr, HitRecord& hr, bool& hit);
	Brick* hitBrick(HitRecord& lhr, HitRecord& hr, bool& hit) const;
	void setBallPosition(const HitRecord& hr);
	void setBallOwner();
	void incrementScore(Player* pPlayer);
	void incrementScore();
	void removeBrick(const Brick* pBrick);
	void ballExit(Player* pPlayer);
	void ballExit();
};


#endif