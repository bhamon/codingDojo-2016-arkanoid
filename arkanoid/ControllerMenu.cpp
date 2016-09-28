#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MainWindow.h"
#include "ControllerMenu.h"
#include "ControllerGame.h"
#include "ControllerLevel.h"
#include "ControllerSettings.h"

namespace arkanoid
{
	ControllerMenu::ControllerMenu(MainWindow& p_mainWindow)
		: Controller(p_mainWindow)
		, m_item(MenuItem::ONE_PLAYER)
	{
	}

	ControllerMenu::~ControllerMenu()
	{
	}

	void ControllerMenu::onKeyDown(int p_virtualKey)
	{
	}

	void ControllerMenu::onKeyUp(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_UP:
				m_item = static_cast<MenuItem>(m_item - 1);
				if(m_item < 0)
				{
					m_item = static_cast<MenuItem>(sizeof(MenuItem) - 1);
				}
				break;
			case VK_DOWN:
				m_item = static_cast<MenuItem>(m_item + 1);
				if(m_item >= sizeof(MenuItem))
				{
					m_item = static_cast<MenuItem>(0);
				}
				break;
			case VK_RETURN:
				switch(m_item)
				{
					case MenuItem::ONE_PLAYER:
					{
						mainWindow().pushController(new ControllerLevel(mainWindow()));
					}
					break;
					case MenuItem::TWO_PLAYERS:
						break;
					case MenuItem::SETTINGS:
					{
						mainWindow().pushController(new ControllerSettings(mainWindow()));
						break;
					}
					case MenuItem::QUIT:
						PostQuitMessage(0);
						break;
				}
				break;
		}
	}

	void ControllerMenu::animate()
	{
	}

	void ControllerMenu::paintScene() const
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		getMainWindow().getPaintHelper().drawText("ARKANOID");

		glColor3f(1.0f, m_item == MenuItem::ONE_PLAYER ? 1.0f : 0.0f, 0.0f);
		glRasterPos2f(100.0f, 200.0f);
		std::string str = "1 " + getMainWindow().getDictionnary().translate(Dictionnary::E_PLAYER);
		getMainWindow().getPaintHelper().drawText(str);
	

		glColor3f(1.0f, m_item == MenuItem::TWO_PLAYERS ? 1.0f : 0.0f, 0.0f);
		glRasterPos2f(100.0f, 300.0f);
		str = "2 " + getMainWindow().getDictionnary().translate(Dictionnary::E_PLAYER)+"s";
		getMainWindow().getPaintHelper().drawText(str);

		glColor3f(1.0f, m_item == MenuItem::SETTINGS ? 1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 400.0f);
		str = getMainWindow().getDictionnary().translate(Dictionnary::E_PARAMETERS);
		getMainWindow().getPaintHelper().drawText(str);

		glColor3f(1.0f, m_item == MenuItem::QUIT ? 1.0f : 0.0f, 0.0f);
		glRasterPos2f(100.0f, 500.0f);
		str = getMainWindow().getDictionnary().translate(Dictionnary::E_QUIT);
		getMainWindow().getPaintHelper().drawText(str);
	}
}