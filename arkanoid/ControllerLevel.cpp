#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <fstream>
#include "MainWindow.h"
#include "ControllerLevel.h"
#include "ControllerGame.h"

namespace arkanoid
{
	ControllerLevel::ControllerLevel(MainWindow& p_mainWindow)
		: Controller(p_mainWindow)
		, m_level(LevelItem::LEVEL_1)
	{
	}

	ControllerLevel::~ControllerLevel()
	{
	}

	void ControllerLevel::onKeyDown(int p_virtualKey)
	{
	}

	void ControllerLevel::onKeyUp(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_UP:
				m_level = static_cast<LevelItem>(m_level - 1);
				if(m_level < 0)
				{
					m_level = static_cast<LevelItem>(sizeof(LevelItem) - 1);
				}
				break;
			case VK_DOWN:
				m_level = static_cast<LevelItem>(m_level + 1);
				if(m_level >= sizeof(LevelItem))
				{
					m_level = static_cast<LevelItem>(0);
				}
				break;
			case VK_RETURN:
				switch(m_level)
				{
					case LevelItem::LEVEL_1:
					{
						std::ifstream str("Levels\\Level01.txt");
						mainWindow().pushController(new ControllerGame(mainWindow(), str));
					}
					break;
					case LevelItem::LEVEL_2:
					{
						std::ifstream str("Levels\\Level02.txt");
						mainWindow().pushController(new ControllerGame(mainWindow(), str));
					}
					break;
					case LevelItem::RETOUR:
					{
						mainWindow().popController();
						break;
					}
				}
				break;
		}
	}

	void ControllerLevel::animate()
	{
	}

	void ControllerLevel::paintScene() const
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		getMainWindow().getPaintHelper().drawText("ARKANOID");

		glColor3f(1.0f, m_level == LevelItem::LEVEL_1?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 200.0f);
		getMainWindow().getPaintHelper().drawText("Level 1");

		glColor3f(1.0f, m_level == LevelItem::LEVEL_2?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 300.0f);
		getMainWindow().getPaintHelper().drawText("Level 2");

		glColor3f(1.0f, m_level == LevelItem::RETOUR?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 400.0f);
		getMainWindow().getPaintHelper().drawText("Retour");
	}
}