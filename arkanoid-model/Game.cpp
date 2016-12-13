#include "Game.h"
#include "Calculator.h"
#include "HitRecord.h"

Game::Game()
	: m_pField(nullptr)
	, m_pBall(nullptr)
	, m_pRacket(nullptr)
	, m_pPlayer(nullptr)
{
	//m_ball.setOwner(&m_player);
}

Game::~Game()
{
}

void Game::setRacket(Racket* pRacket)
{
	m_pRacket = pRacket;
}

void Game::setBall(Ball* pBall)
{
	m_pBall = pBall;
}

void Game::setField(Field* pField)
{
	m_pField = pField;
}

void Game::setPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

const Field* Game::getField() const
{
	return m_pField;
}

const Ball* Game::getBall() const
{
	return m_pBall;
}

const Racket* Game::getRacket() const
{
	return m_pRacket;
}

const Player* Game::getPlayer() const
{
	return m_pPlayer;
}


void Game::tick()
{
	ballMove();

	forceRacketIntoField();

	while (true)
	{
		bool hit = false;
		Brick* pBrickRef = nullptr;

		HitRecord hr;
		HitRecord lhr;

		if (hitTopField(lhr) == true && lhr.getRollback() > hr.getRollback())
		{
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

		pBrickRef = hitBrick(lhr, hr, hit);

		if (hit)
		{
			setBallPosition(hr);

			if (pBrickRef != nullptr)
			{
				pBrickRef->strength()--;
				incrementScore();

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

void Game::ballMove()
{
	Calculator::move(*m_pBall, 1.0f);
}

void Game::forceRacketIntoField(Racket* pRacket)
{
	if (pRacket->right() > m_pField->getWidth())
		pRacket->position().setX(m_pField->getWidth() - Racket::WIDTH / 2.f);

	if (pRacket->left() < 0.f)
		pRacket->position().setX(Racket::WIDTH / 2.f);
}

void Game::forceRacketIntoField()
{
	forceRacketIntoField(m_pRacket);
}

bool Game::hitTopField(HitRecord& lhr) const
{
	return Calculator::hit(*m_pBall, math::Point2<float>(0.0f, 0.0f), math::Point2<float>(m_pField->getWidth(), 0.0f), lhr);
}

bool Game::hitRightField(HitRecord& lhr) const
{
	return Calculator::hit(*m_pBall, math::Point2<float>(m_pField->getWidth(), 0.0f), math::Point2<float>(m_pField->getWidth(), m_pField->getHeight()), lhr);
}

bool Game::hitBottomField(HitRecord& lhr) const
{
	return Calculator::hit(*m_pBall, math::Point2<float>(m_pField->getWidth(), m_pField->getHeight()), math::Point2<float>(0.0f, m_pField->getHeight()), lhr);
}

bool Game::hitLeftField(HitRecord& lhr) const
{
	return Calculator::hit(*m_pBall, math::Point2<float>(0.0f, m_pField->getHeight()), math::Point2<float>(0.0f, 0.0f), lhr);
}

void Game::hitRacket(const Player* pPlayer, const Racket* pRacket, HitRecord& lhr, HitRecord& hr, bool& hit)
{
	if (Calculator::hit(*m_pBall, *pRacket, *m_pField, lhr) == true)
	{
		hit = true;
		hr = lhr;
		float x = (hr.getHitPoint().getX() - pRacket->getPosition().getX()) / Racket::WIDTH;
		if (x > 0.5f) x = 0.5f;
		if (x < -0.5f) x = -0.5f;
		math::Normal2<float> norm = hr.getNormal();
		const float coef = 1.0f;
		norm.setX(norm.getX() + (x * coef));
		norm.normalize();
		hr.setNormal(norm);
		setBallOwner(pPlayer);
	}
}

void Game::hitRacket(HitRecord& lhr, HitRecord& hr, bool& hit)
{
	hitRacket(m_pPlayer, m_pRacket, lhr, hr, hit);
}

void Game::setBallOwner(const Player* pPlayer)
{
	if (m_pBall != nullptr)
	{
		m_pBall->setOwner(pPlayer);
	}
}

Brick* Game::hitBrick(HitRecord& lhr, HitRecord& hr, bool& hit) const
{
	Brick* pBrick = nullptr;
	for (Brick& brick : *m_pField)
	{
		if (Calculator::hit(*m_pBall, brick, lhr) && lhr.getRollback() > hr.getRollback())
		{
			pBrick = &brick;
			hr = lhr;
			hit = true;
		}
	}
	return pBrick;
}

void Game::setBallPosition(const HitRecord& hr)
{
	m_pBall->position() = hr.getNewPosition();
	Calculator::bounce(*m_pBall, hr.getNormal());
	Calculator::move(*m_pBall, hr.getRollback() + 0.1f);
}

void Game::setBallOwner()
{
	setBallOwner(m_pPlayer);
}

void Game::incrementScore(Player* pPlayer)
{
	if (m_pBall->getOwner() == pPlayer)
	{
		pPlayer->incrementScore();
	}
}

void Game::incrementScore()
{
	incrementScore(m_pPlayer);
}

void Game::removeBrick(const Brick* pBrick)
{
	m_pField->removeBrick(*pBrick);
}

void Game::ballExit(Player* pPlayer)
{
	pPlayer->lostOneLife();
	m_pBall->setVelocity(math::Vector2<float>(0.0f, 0.0f));
}

void Game::ballExit()
{
	ballExit(m_pPlayer);
}

bool Game::isFinished() const
{
	return m_pField->getBrickNumber() == 0 || m_pPlayer->getLives() == 0;
}