#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <sstream>
#include "MainWindow.h"
#include "ControllerGame.h"

namespace arkanoid
{
	ControllerGame::ControllerGame(MainWindow& p_mainWindow)
		: Controller(p_mainWindow)
		, m_ball(math::Point2<float>(400.0f, (500.0f - Racket::OFFSET - Racket::HEIGHT / 2 - Ball::RADIUS - 0.1f)), math::Vector2<float>(0.0f, 0.0f))
		, m_racket(0.0)
		, m_field(500.0, 500.0)
		, m_player("Joueur")
		, m_game(m_field, m_ball, m_racket, m_player)
		, m_goLeft(false)
		, m_goRight(false)
	{
		// They want to invade us!
		math::Vector2<float> ref(m_field.getWidth() / 2.0f, m_field.getHeight() / 2.0f);
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -3.0f, Brick::HEIGHT * -3.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 3.0f, Brick::HEIGHT * -3.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -2.0f, Brick::HEIGHT * -2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 2.0f, Brick::HEIGHT * -2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -3.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -2.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -1.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 0.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 1.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 2.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 3.0f, Brick::HEIGHT * -1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -4.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -3.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -1.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 0.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 1.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 3.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 4.0f, Brick::HEIGHT * 0.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -5.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -4.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -3.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -2.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -1.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 0.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 1.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 2.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 3.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 4.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 5.0f, Brick::HEIGHT * 1.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -5.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -3.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -2.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -1.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 0.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 1.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 2.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 3.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 5.0f, Brick::HEIGHT * 2.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -5.0f, Brick::HEIGHT * 3.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -3.0f, Brick::HEIGHT * 3.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 3.0f, Brick::HEIGHT * 3.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 5.0f, Brick::HEIGHT * 3.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -2.0f, Brick::HEIGHT * 4.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * -1.0f, Brick::HEIGHT * 4.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 1.0f, Brick::HEIGHT * 4.0f) + ref, 2u));
		m_field.addBrick(Brick(math::Point2<float>(Brick::WIDTH * 2.0f, Brick::HEIGHT * 4.0f) + ref, 2u));
	}

	ControllerGame::~ControllerGame()
	{
	}

	void ControllerGame::onKeyDown(int p_virtualKey)
	{
		switch(p_virtualKey)
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
		switch(p_virtualKey)
		{
			case VK_LEFT:
				m_goLeft = false;
				break;
			case VK_RIGHT:
				m_goRight = false;
				break;
			case VK_UP:
				if((m_ball.getVelocity().getX() == 0.0f) && (m_ball.getVelocity().getY() == 0.0f))
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
		if(m_game.isFinished() == false)
		{
			if(m_goLeft)
			{
				m_racket.position() -= 0.2f;
			}

			if(m_goRight)
			{
				m_racket.position() += 0.2f;
			}

			if((m_ball.getVelocity().getX() == 0.0f) && (m_ball.getVelocity().getY() == 0.0f))
			{
				m_ball.position().x() = m_racket.position();
			}

			m_game.tick();
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
		ost << "lives: " << m_player.getLives();
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

				glPushMatrix();
				{
					glTranslatef(0.0f, m_field.getHeight() - Racket::OFFSET, 0.0f);

					glBegin(GL_QUADS);
					glColor3f(0.0f, 0.0f, 1.0f);
					glVertex3f(m_racket.getPosition() - m_racket.WIDTH / 2.0f, -m_racket.HEIGHT, 0.0f);
					glVertex3f(m_racket.getPosition() + m_racket.WIDTH / 2.0f, -m_racket.HEIGHT, 0.0f);
					glVertex3f(m_racket.getPosition() + m_racket.WIDTH / 2.0f, 0.0, 0.0f);
					glVertex3f(m_racket.getPosition() - m_racket.WIDTH / 2.0f, 0.0, 0.0f);
					glEnd();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(m_ball.getPosition().getX(), m_ball.getPosition().getY(), 0.0f);
					glColor3f(1.0f, 0.0f, 0.0f);
					gluDisk(getMainWindow().getPaintHelper().getQuadric(), 0.0, Ball::RADIUS, 10, 10);
				}
				glPopMatrix();

				for(auto brick : m_field.getListBricks())
				{
					glPushMatrix();
					{
						glTranslatef(brick.getPosition().getX(), brick.getPosition().getY(), 0.0f);

						glBegin(GL_QUADS);
						glColor3f(brick.getStrength() * 0.4f, 0.0f, 0.0f);
						glVertex3f(-Brick::WIDTH / 2.0f, -Brick::HEIGHT / 2.0f, 0.0f);
						glVertex3f(-Brick::WIDTH / 2.0f, +Brick::HEIGHT / 2.0f, 0.0f);
						glVertex3f(+Brick::WIDTH / 2.0f, +Brick::HEIGHT / 2.0f, 0.0f);
						glVertex3f(+Brick::WIDTH / 2.0f, -Brick::HEIGHT / 2.0f, 0.0f);
						glEnd();
					}
					glPopMatrix();
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
}