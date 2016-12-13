#include "MultiPlayerGame.h"
#include "Calculator.h"
#include "HitRecord.h"

MultiPlayerGame::MultiPlayerGame()
	: Game()
	, m_pRacket2(nullptr)
	, m_pPlayer2(nullptr)
{
}

MultiPlayerGame::~MultiPlayerGame()
{
}

void MultiPlayerGame::setRacket2(Racket* pRacket)
{
	m_pRacket2 = pRacket;
}

void MultiPlayerGame::setPlayer2(Player* pPlayer)
{
	m_pPlayer2 = pPlayer;
}

const Racket* MultiPlayerGame::getRacket2() const
{
	return m_pRacket2;
}

const Player* MultiPlayerGame::getPlayer2() const
{
	return m_pPlayer2;
}

void MultiPlayerGame::tick()
{
	ballMove();

	forceRacketIntoField();
	forceRacketIntoField(m_pRacket2);

	while (true)
	{
		bool hit = false;
		Brick* pBrickRef = nullptr;

		HitRecord hr;
		HitRecord lhr;

		if (hitTopField(lhr) == true && lhr.getRollback() > hr.getRollback())
		{
			setBallOwner(m_pPlayer2);
			ballExit(m_pPlayer2);
			hit = true;
			hr = lhr;
		}
		if (hitRightField(lhr) == true && lhr.getRollback() > hr.getRollback())
		{
			hit = true;
			hr = lhr;
		}
		//Bottom border
		if (hitBottomField(lhr) == true && lhr.getRollback() > hr.getRollback())
		{
			setBallOwner();
			ballExit();
			hr = lhr;
			break;
		}
		if (hitLeftField(lhr) && lhr.getRollback() > hr.getRollback())
		{
			hit = true;
			hr = lhr;
		}

		hitRacket(lhr, hr, hit);
		hitRacket(m_pPlayer2, m_pRacket2, lhr, hr, hit);

		pBrickRef = hitBrick(lhr, hr, hit);

		if (hit)
		{
			setBallPosition(hr);

			if (pBrickRef != nullptr)
			{
				pBrickRef->strength()--;
				incrementScore();
				incrementScore(m_pPlayer2);

				if (pBrickRef->strength() == 0)
				{
					removeBrick(pBrickRef);
				}
			}
		}
		else
		{
			break;
		}
	}
}

bool MultiPlayerGame::isFinished() const
{
	return Game::isFinished() || m_pPlayer2->getLives() == 0;
}