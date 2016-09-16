#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameEngine.h"
#include <arkanoid-model\Calculator.h>
#include <arkanoid-model\HitRecord.h>
#include <sstream>

const int FIELD_WIDTH = 500;
const int FIELD_HEIGHT = 900;

namespace arkanoid
{
	GameEngine::GameEngine() :
		  m_quadric(0)
		, m_ball(math::Point2<float>(400.0f, (FIELD_HEIGHT - Racket::OFFSET - Racket::HEIGHT - Ball::RADIUS)), math::Vector2<float>(0.0f, 0.0f))
		, m_racket(0.0)
		, m_field(FIELD_WIDTH, FIELD_HEIGHT)
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

		m_quadric = gluNewQuadric();
	}

	GameEngine::~GameEngine()
	{
		gluDeleteQuadric(m_quadric);
	}

	void GameEngine::animate()
	{
		if(m_game.isFinished() == false)
		{
			float racketMove = Racket::WIDTH / 10.f;
			if(m_goLeft)
			{
				m_racket.position() -= racketMove;
			}

			if(m_goRight)
			{
				m_racket.position() += racketMove;
			}

			if((m_ball.getVelocity().getX() == 0.0f) && (m_ball.getVelocity().getY() == 0.0f))
			{
				m_ball.position().x() = m_racket.position(); 
			}
			
			m_game.tick();
		}
	}

	void GameEngine::paintScene() const
	{
		glEnable(GL_MULTISAMPLE);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char*>("ARKANOID"));
		glRasterPos2f(100.0f, 150.0f);
		std::ostringstream ost;
		ost << "score: " << m_player.getScore() ;
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char*>(ost.str().c_str()));
		
		ost.str("");
		ost << "lives: " << m_player.getLives();
		glRasterPos2f(400.0f, 150.0f);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char*>(ost.str().c_str()));

		glPushMatrix();
		{
			glTranslatef(150.0f, 100.0f, 0.0f);

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
					gluDisk(m_quadric, 0.0, Ball::RADIUS, 10, 10);
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

	void GameEngine::onResize(unsigned int p_width, unsigned int p_height)
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

	void GameEngine::onKeyDown(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case GLUT_KEY_LEFT:
				m_goLeft = true;
				break;
			case GLUT_KEY_RIGHT:
				m_goRight = true;
				break;
		}
	}

	void GameEngine::onKeyUp(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case GLUT_KEY_LEFT:
				m_goLeft = false;
				break;
			case GLUT_KEY_RIGHT:
				m_goRight = false;
				break;
			case GLUT_KEY_UP:

				if((m_ball.getVelocity().getX() == 0.0f) && (m_ball.getVelocity().getY() == 0.0f))
				{
					float initialVelocity = Ball::RADIUS / 2;
					m_ball.setVelocity(math::Vector2<float>(-initialVelocity, -initialVelocity));
				}
				break;
		}
	}
};