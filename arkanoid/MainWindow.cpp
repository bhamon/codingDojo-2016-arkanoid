#include "MainWindow.h"
#include <arkanoid-model\Calculator.h>
#include <arkanoid-model\HitRecord.h>

namespace arkanoid
{
	MainWindow::MainWindow(unsigned int p_width, unsigned int p_height, const std::string& p_title)
		: arkanoid::Window(p_width, p_height, p_title)
		, m_font(0)
		, m_quadric(0)
		, m_ball(math::Point2<float>(10.0f, 10.0f), math::Vector2<float>(0.1f, 0.1f))
		, m_bricks()
	{
		m_bricks.push_back(Brick(math::Point2<float>(150.0f, 150.0f), 3u));
		m_bricks.push_back(Brick(math::Point2<float>(310.0f, 150.0f), 3u));
		m_bricks.push_back(Brick(math::Point2<float>(150.0f, 220.0f), 3u));
		m_bricks.push_back(Brick(math::Point2<float>(310.0f, 310.0f), 3u));

		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		m_font = glGenLists(96);
		HFONT font = CreateFont(
			-24,								// Height (based on CHARACTER, not CELL)
			0,									// Cell width
			0,									// Angle of escapment
			0,									// Orientation angle
			FW_BOLD,							// Weight
			0,									// Italic
			0,									// Underline
			0,									// Strikeout
			ANSI_CHARSET,						// Charset
			OUT_TT_PRECIS,						// Output precision: select TTF by default
			CLIP_DEFAULT_PRECIS,				// Clipping precision
			ANTIALIASED_QUALITY,				// Output quality: antialiased
			FF_DONTCARE | DEFAULT_PITCH,		// Family and pitch
			"Bauhaus 93"						// Name
		);

		HFONT oldfont = static_cast<HFONT>(SelectObject(m_deviceContext, font));
		wglUseFontBitmaps(m_deviceContext, 32, 96, m_font);
		SelectObject(m_deviceContext, oldfont);
		DeleteObject(font);

		m_quadric = gluNewQuadric();
	}

	MainWindow::~MainWindow()
	{
		gluDeleteQuadric(m_quadric);
		glDeleteLists(m_font, 96);
	}

	void MainWindow::animate()
	{
		Calculator::move(m_ball, 1.0f);

		while(true)
		{
			bool hit = false;
			HitRecord hr;
			HitRecord lhr;

			if(hit |= Calculator::hit(m_ball, math::Point2<float>(0.0f, 0.0f), math::Point2<float>(400.0f, 0.0f), lhr) && lhr.getRollback() > hr.getRollback())
			{
				hr = lhr;
			}
			if(hit |= Calculator::hit(m_ball, math::Point2<float>(400.0f, 0.0f), math::Point2<float>(400.0f, 400.0f), lhr) && lhr.getRollback() > hr.getRollback())
			{
				hr = lhr;
			}
			if(hit |= Calculator::hit(m_ball, math::Point2<float>(400.0f, 400.0f), math::Point2<float>(0.0f, 400.0f), lhr) && lhr.getRollback() > hr.getRollback())
			{
				hr = lhr;
			}
			if(hit |= Calculator::hit(m_ball, math::Point2<float>(0.0f, 400.0f), math::Point2<float>(0.0f, 0.0f), lhr) && lhr.getRollback() > hr.getRollback())
			{
				hr = lhr;
			}

			for(auto brick : m_bricks)
			{
				if(hit |= Calculator::hit(m_ball, brick, lhr) && lhr.getRollback() > hr.getRollback())
				{
					hr = lhr;
				}
			}

			if(hit)
			{
				m_ball.position() = hr.getNewPosition();
				//	m_ball.position() += -hr.getRollback() * m_ball.getVelocity();
				Calculator::bounce(m_ball, hr.getNormal());
				Calculator::move(m_ball, hr.getRollback() + 0.1f);
			}
			else
			{
				break;
			}
		}
	}

	void MainWindow::paintScene() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_font - 32);
		glCallLists(8, GL_UNSIGNED_BYTE, "ARKANOID");
		glRasterPos2f(100.0f, 150.0f);
		glListBase(m_font - 32);
		glCallLists(8, GL_UNSIGNED_BYTE, "score: ");
		glPopAttrib();

		glPushMatrix();
		{
			glTranslatef(100.0f, 100.0f, 0.0f);

			glPushMatrix();
			{
				glTranslatef(0.0f, 100.0f, 0.0f);

				glBegin(GL_QUADS);
				glColor3f(1.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 400.0f, 0.0f);
				glVertex3f(400.0f, 400.0f, 0.0f);
				glVertex3f(400.0f, 0.0f, 0.0f);
				glEnd();

				glPushMatrix();
				{
					glTranslatef(m_ball.getPosition().getX(), m_ball.getPosition().getY(), 0.0f);
					glColor3f(1.0f, 0.0f, 0.0f);
					gluDisk(m_quadric, 0.0, 10.0, 20, 20);
				}
				glPopMatrix();

				for(auto brick : m_bricks)
				{
					glPushMatrix();
					{
						glTranslatef(brick.getPosition().getX(), brick.getPosition().getY(), 0.0f);

						glBegin(GL_QUADS);
						glColor3f(0.0f, 0.0f, 0.0f);
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
		if(p_virtualKey == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
	}

	void MainWindow::onKeyUp(int p_virtualKey)
	{
	}
};