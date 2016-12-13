#include "ControllerMultiGame.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <sstream>

#include "arkanoid-model/MultiPlayerGame.h"
#include "MainWindow.h"

namespace arkanoid
{

	ControllerMultiGame::ControllerMultiGame(MainWindow& p_mainWindow, std::istream& file)
		: ControllerGame(p_mainWindow, file, new MultiPlayerGame())
		, m_player2("joueur 2")
		, m_racket2(math::Point2<float>(200.f, Racket::OFFSET))
		, m_goLeft2(false)
		, m_goRight2(false)
	{
		MultiPlayerGame* pMultiPlayerGame = getGame();
		pMultiPlayerGame->setPlayer2(&m_player2);
		pMultiPlayerGame->setRacket2(&m_racket2);
	}

	ControllerMultiGame::~ControllerMultiGame()
	{
	}

	void ControllerMultiGame::onKeyDown(int p_virtualKey)
	{
		ControllerGame::onKeyDown(p_virtualKey);
		switch (p_virtualKey)
		{
		case 'Q':
			m_goLeft2 = true;
			break;
		case 'D':
			m_goRight2 = true;
			break;
		}
	}

	void ControllerMultiGame::onKeyUp(int p_virtualKey)
	{
		ControllerGame::onKeyUp(p_virtualKey);
		switch (p_virtualKey)
		{
		case 'Q':
			m_goLeft2 = false;
			break;
		case 'D':
			m_goRight2 = false;
			break;
		case 'Z':
			if (ballHasStopped() == 1.f)
			{
				setBallVelocity(math::Vector2<float>(0.1f, 0.1f));
			}
			break;
		}
	}

	void ControllerMultiGame::animate()
	{
		if (gameIsFinished() == false)
		{
			if (m_goLeft2)
			{
				m_racket2.position().setX(m_racket2.position().getX() - 0.2f);
			}

			if (m_goRight2)
			{
				m_racket2.position().setX(m_racket2.position().getX() + 0.2f);
			}
		}
		ControllerGame::animate();
	}

	void ControllerMultiGame::paintScene() const
	{
		ControllerGame::paintScene();

		glColor3f(1.0f, 1.0f, 0.0f);

		glRasterPos2f(650.0f, 150.0f);
		std::ostringstream ost;
		ost << "score: " << m_player2.getScore();
		getMainWindow().getPaintHelper().drawText(ost.str());

		ost.str("");
		ost << getMainWindow().getDictionnary().translate(Dictionnary::E_LIFE) << ": " << m_player2.getLives();
		glRasterPos2f(900.0f, 150.0f);
		getMainWindow().getPaintHelper().drawText(ost.str());

		glPushMatrix();
		{
			glTranslatef(100.0f, 100.0f, 0.0f);

			glPushMatrix();
			{
				glTranslatef(0.0f, 100.0f, 0.0f);

				drawRacket(m_racket2);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	MultiPlayerGame* ControllerMultiGame::getGame()
	{
		return dynamic_cast<MultiPlayerGame*>(ControllerGame::getGame());
	}
}