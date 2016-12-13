#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <sstream>
#include "MainWindow.h"
#include "ControllerGame.h"
#include "arkanoid-model/FieldLoader.h"
namespace arkanoid
{
	ControllerGame::ControllerGame(MainWindow& p_mainWindow, std::istream& file)
		: Controller(p_mainWindow)
		, m_ball(math::Point2<float>(400.0f, (500.0f - Racket::OFFSET - Racket::HEIGHT / 2 - Ball::RADIUS - 0.1f)), math::Vector2<float>(0.0f, 0.0f))
		, m_racket(math::Point2<float>(.0f, 500.0f - Racket::OFFSET))
		, m_field(500.0, 500.0)
		, m_player("Joueur")
		, m_pGame(new Game())
		, m_goLeft(false)
		, m_goRight(false)
	{
		m_pGame->setField(&m_field);
		m_pGame->setBall(&m_ball);
		m_pGame->setRacket(&m_racket);
		m_pGame->setPlayer(&m_player);
		m_pGame->setBallOwner(&m_player);

		FieldLoader::load(file, m_field);
	}

	ControllerGame::ControllerGame(MainWindow& p_mainWindow, std::istream& file, Game* pGame)
		: Controller(p_mainWindow)
		, m_ball(math::Point2<float>(400.0f, (500.f - Racket::OFFSET - Racket::HEIGHT / 2 - Ball::RADIUS - 0.1f)), math::Vector2<float>(0.0f, 0.0f))
		, m_racket(math::Point2<float>(250.f, 500.f - Racket::OFFSET))
		, m_field(500.f, 500.f)
		, m_player("Joueur")
		, m_pGame(pGame)
		, m_goLeft(false)
		, m_goRight(false)
	{
		m_pGame->setField(&m_field);
		m_pGame->setBall(&m_ball);
		m_pGame->setRacket(&m_racket);
		m_pGame->setPlayer(&m_player);
		m_pGame->setBallOwner(&m_player);

		FieldLoader::load(file, m_field);
	}

	ControllerGame::~ControllerGame()
	{
		delete m_pGame;
	}

	void ControllerGame::onKeyDown(int p_virtualKey)
	{
		switch (p_virtualKey)
		{
		case VK_LEFT:
			m_goLeft = true;
			break;
		case VK_RIGHT:
			m_goRight = true;
			break;
		}
	}

	void ControllerGame::onKeyUp(int p_virtualKey)
	{
		switch (p_virtualKey)
		{
		case VK_LEFT:
			m_goLeft = false;
			break;
		case VK_RIGHT:
			m_goRight = false;
			break;
		case VK_UP:
			if (ballHasStopped() == true)
			{
				m_ball.setVelocity(math::Vector2<float>(-0.1f, -0.1f));
			}
			break;
		case VK_ESCAPE:
			mainWindow().popController();
		}
	}

	void ControllerGame::animate()
	{
		if (gameIsFinished() == false)
		{
			if (m_goLeft)
			{
				m_racket.position().setX(m_racket.position().getX() - 0.2f);
			}

			if (m_goRight)
			{
				m_racket.position().setX(m_racket.position().getX() + 0.2f);
			}

			if (ballHasStopped() == true)
			{
				m_ball.position().y() = m_racket.top() - Ball::RADIUS;
				m_ball.position().x() = m_racket.getPosition().getX();
			}

			m_pGame->tick();
		}
		else
		{
			mainWindow().popController();
		}
	}

	void ControllerGame::paintScene() const
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		getMainWindow().getPaintHelper().drawText("ARKANOID");

		glRasterPos2f(100.0f, 150.0f);
		std::ostringstream ost;
		ost << "score: " << m_player.getScore();
		getMainWindow().getPaintHelper().drawText(ost.str());

		ost.str("");
		ost << getMainWindow().getDictionnary().translate(Dictionnary::E_LIFE) << ": " << m_player.getLives();
		glRasterPos2f(400.0f, 150.0f);
		getMainWindow().getPaintHelper().drawText(ost.str());

		glPushMatrix();
		{
			glTranslatef(100.0f, 100.0f, 0.0f);

			glPushMatrix();
			{
				glTranslatef(0.0f, 100.0f, 0.0f);

				glBegin(GL_QUADS);
				glColor3f(1.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, m_field.getHeight(), 0.0f);
				glVertex3f(m_field.getWidth(), m_field.getHeight(), 0.0f);
				glVertex3f(m_field.getWidth(), 0.0f, 0.0f);
				glEnd();

				drawRacket(m_racket);

				glPushMatrix();
				{
					glTranslatef(m_ball.getPosition().getX(), m_ball.getPosition().getY(), 0.0f);
					glColor3f(1.0f, 0.0f, 0.0f);
					gluDisk(getMainWindow().getPaintHelper().getQuadric(), 0.0, Ball::RADIUS, 10, 10);
				}
				glPopMatrix();

				for (const auto& brick : m_field.getListBricks())
				{
					drawBrick(brick);
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	Game* ControllerGame::getGame()
	{
		return m_pGame;
	}

	void ControllerGame::drawBrick(const Brick& brick) const
	{
		glPushMatrix();
		{
			glTranslatef(brick.left(), brick.top(), 0.f);

			glBegin(GL_QUADS);
			glColor3f(brick.getStrength() * 0.4f, 0.0f, 0.0f);
			glVertex3f(0.f, 0.f, 0.f);
			glVertex3f(Brick::WIDTH, 0.f, 0.f);
			glVertex3f(Brick::WIDTH, Brick::HEIGHT, 0.f);
			glVertex3f(0.f, Brick::HEIGHT, 0.f);
			glEnd();
		}
		glPopMatrix();
	}

	void ControllerGame::drawRacket(const Racket& racket) const
	{
		glPushMatrix();
		{
			glTranslatef(racket.left(), racket.top(), 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.f, 0.f, 0.f);
			glVertex3f(Racket::WIDTH, 0.f, 0.f);
			glVertex3f(Racket::WIDTH, Racket::HEIGHT, 0.f);
			glVertex3f(0.f, Racket::HEIGHT, 0.f);
			glEnd();
		}
		glPopMatrix();
	}

	bool ControllerGame::gameIsFinished() const
	{
		return m_pGame->isFinished();
	}

	bool ControllerGame::ballHasStopped() const
	{
		return m_ball.getVelocity().getX() == 0.f && m_ball.getVelocity().getY() == 0.f;
	}

	void ControllerGame::setBallVelocity(const math::Vector2<float>& velocity)
	{
		m_ball.setVelocity(velocity);
	}
}