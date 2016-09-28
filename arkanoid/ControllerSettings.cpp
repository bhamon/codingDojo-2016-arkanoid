#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MainWindow.h"
#include "ControllerSettings.h"
#include "ControllerLanguages.h"

namespace arkanoid
{
	ControllerSettings::ControllerSettings(MainWindow& p_mainWindow)
		: Controller(p_mainWindow)
		, m_settingsItem(SettingsItem::E_LANGUAGE)
	{
	}

	ControllerSettings::~ControllerSettings()
	{
	}

	void ControllerSettings::onKeyDown(int p_virtualKey)
	{
	}

	void ControllerSettings::onKeyUp(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_UP:
				m_settingsItem = static_cast<SettingsItem>(m_settingsItem - 1);
				if(m_settingsItem < 0)
				{
					m_settingsItem = static_cast<SettingsItem>(sizeof(m_settingsItem) - 1);
				}
				break;
			case VK_DOWN:
				m_settingsItem = static_cast<SettingsItem>(m_settingsItem + 1);
				if(m_settingsItem >= sizeof(SettingsItem))
				{
					m_settingsItem = static_cast<SettingsItem>(0);
				}
				break;
			case VK_RETURN:
				switch(m_settingsItem)
				{
					case SettingsItem::E_LANGUAGE:
					{
						mainWindow().pushController(new ControllerLanguages(mainWindow()));
					}
					break;
					case SettingsItem::E_RETOUR:
					{
						mainWindow().popController();
						break;
					}
				}
				break;
		}
	}

	void ControllerSettings::animate()
	{
	}

	void ControllerSettings::paintScene() const
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		getMainWindow().getPaintHelper().drawText("ARKANOID");

		glColor3f(1.0f, m_settingsItem == SettingsItem::E_LANGUAGE?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 200.0f);
		getMainWindow().getPaintHelper().drawText("Language");

		glColor3f(1.0f, m_settingsItem == SettingsItem::E_RETOUR?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 300.0f);
		getMainWindow().getPaintHelper().drawText("Return");
	}
}