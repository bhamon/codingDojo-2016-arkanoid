#include "MainWindow.h"
#include <arkanoid-model\Calculator.h>
#include <arkanoid-model\HitRecord.h>
#include <sstream>

namespace arkanoid
{
	MainWindow::MainWindow(unsigned int p_width, unsigned int p_height, const std::string& p_title)
		: arkanoid::Window(p_width, p_height, p_title)
		, m_paintHelper(m_deviceContext)
		, m_ball(math::Point2<float>(400.0f, (500.0f - Racket::OFFSET - Racket::HEIGHT/2 - Ball::RADIUS - 0.1f)), math::Vector2<float>(0.0f, 0.0f))
		, m_racket(0.0)
		, m_field(500.0, 500.0)
		, m_player("Player")
		, m_game( m_field, m_ball, m_racket, m_player)
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

		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}

	MainWindow::~MainWindow()
	{
	}

	void MainWindow::animate()
	{
		if(m_game.isFinished() == false)
		{
			if(m_goLeft)
			{
				m_racket.position() -= 0.2;
			}

			if(m_goRight)
			{
				m_racket.position() += 0.2;
			}

			if((m_ball.getVelocity().getX() == 0.0f) && (m_ball.getVelocity().getY() == 0.0f))
			{
				m_ball.position().x() = m_racket.position(); 
			}
			
			m_game.tick();
		}
	}

	void MainWindow::paintScene() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		m_paintHelper.drawText("ARKANOID");
		
		glRasterPos2f(100.0f, 150.0f);
		std::ostringstream ost;
		ost << "score: " << m_player.getScore();
		m_paintHelper.drawText(ost.str());
		
		ost.str("");
		ost << "lives: " << m_player.getLives();
		glRasterPos2f(400.0f, 150.0f);
		m_paintHelper.drawText(ost.str());

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
					gluDisk(m_paintHelper.getQuadric(), 0.0, Ball::RADIUS, 10, 10);
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

	void MainWindow::onResize(unsigned int p_width, unsigned int p_height)
	{
		glViewport(0, 0, p_width, p_height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, 0, p_width, p_height, -1, 1);

		glTranslatef(-1.0f, 1.0f, 0.0f);
		glScalef(1.0f / static_cast<float>(p_width), -1.0f / static_cast<float>(p_height), 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void MainWindow::onKeyDown(int p_virtualKey)
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

	void MainWindow::onKeyUp(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
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
		}
	}
};