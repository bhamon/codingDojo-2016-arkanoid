#include "Game.h"
#include "Calculator.h"
#include "HitRecord.h"

Game::Game(Field &field, Ball &ball, Racket &racket, Player &player) :
m_field(field), m_ball(ball), m_racket(racket), m_player(player)
{
}

const Field & Game::getField() const
{
	return m_field;
}

const Ball & Game::getBall() const
{
	return m_ball;
}

const Racket &Game::getRacket() const
{
	return m_racket;
}

const Player &Game::getPlayer() const
{
	return m_player;
}

void Game::tick()
{
	Calculator::move(m_ball, 1.0f);

	if(m_racket.getPosition() > m_field.getWidth() - m_racket.WIDTH / 2)
		m_racket.setPosition(m_field.getWidth() - m_racket.WIDTH / 2);

	if(m_racket.getPosition() < m_racket.WIDTH / 2)
		m_racket.setPosition( m_racket.WIDTH / 2);

	while(true)
	{
		bool hit = false;
		Brick *brickRef = 0;

		HitRecord hr;
		HitRecord lhr;

		if(Calculator::hit(m_ball, math::Point2<float>(0.0f, 0.0f), math::Point2<float>(m_field.getWidth(), 0.0f), lhr) && lhr.getRollback() > hr.getRollback())
		{
			hit = true;
			hr = lhr;
		}
		if(Calculator::hit(m_ball, math::Point2<float>(m_field.getWidth(), 0.0f), math::Point2<float>(m_field.getWidth(), m_field.getHeight()), lhr) && lhr.getRollback() > hr.getRollback())
		{
			hit = true;
			hr = lhr;
		}
		//Bottom border
		if(Calculator::hit(m_ball, math::Point2<float>(m_field.getWidth(), m_field.getHeight()), math::Point2<float>(0.0f, m_field.getHeight()), lhr) && lhr.getRollback() > hr.getRollback())
		{
			m_player.setLives(m_player.getLives() - 1);
			m_ball.setVelocity(math::Vector2<float>(0.0f, 0.0f));
			m_ball.position().y() = (m_field.getHeight() - Racket::OFFSET - Racket::HEIGHT / 2 - Ball::RADIUS - 0.1f);
			hr = lhr;
			break;
		}
		if(Calculator::hit(m_ball, math::Point2<float>(0.0f, m_field.getHeight()), math::Point2<float>(0.0f, 0.0f), lhr) && lhr.getRollback() > hr.getRollback())
		{
			hit = true;
			hr = lhr;
		}
		if(Calculator::hit(m_ball, m_racket, m_field, lhr))
		{
			hit = true;
			hr = lhr;
			float x = (hr.getHitPoint().getX() - m_racket.getPosition()) / Racket::WIDTH;
			if(x > 0.5f) x = 0.5f;
			if(x < -0.5f) x = -0.5f;
			math::Normal2<float> norm = hr.getNormal() ;
			const float coef = 1.0f ;
			norm.setX(norm.getX() + (x * coef)) ;
			norm.normalize() ;
			hr.setNormal(norm) ;
		}

		for(Brick& brick : m_field)
		{
			if(Calculator::hit(m_ball, brick, lhr) && lhr.getRollback() > hr.getRollback())
			{
				brickRef = &brick;
				hr = lhr;
				hit = true;
			}
		}

		if(hit)
		{
			m_ball.position() = hr.getNewPosition();
			//m_ball.position() += -hr.getRollback() * m_ball.getVelocity();
			Calculator::bounce(m_ball, hr.getNormal());
			Calculator::move(m_ball, hr.getRollback() + 0.1f);

			if(brickRef)
			{
				brickRef->strength()--;

				if(brickRef->strength() == 0)
				{
					m_field.removeBrick(*brickRef);
					m_player.setScore(m_player.getScore() + 1);
				}
			}
		}
		else
		{
			break;
		}

	}

}

Game::~Game()
{
}

bool 
Game::isFinished()
{
	return m_field.getBrickNumber() == 0 || m_player.getLives() == 0;
}