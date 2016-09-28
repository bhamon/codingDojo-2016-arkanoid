#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MainWindow.h"
#include "ControllerLanguages.h"

namespace arkanoid
{
	ControllerLanguages::ControllerLanguages(MainWindow& p_mainWindow)
		: Controller(p_mainWindow), m_languageItem(LanguageEnum::E_EN)
	{
	}

	ControllerLanguages::~ControllerLanguages()
	{
	}

	void ControllerLanguages::onKeyDown(int p_virtualKey)
	{
	}

	void ControllerLanguages::onKeyUp(int p_virtualKey)
	{
		switch(p_virtualKey)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_UP:
				m_languageItem = static_cast<LanguageEnum>(m_languageItem - 1);
				if(m_languageItem < 0)
				{
					m_languageItem = static_cast<LanguageEnum>(sizeof(m_languageItem) - 1);
				}
				break;
			case VK_DOWN:
				m_languageItem = static_cast<LanguageEnum>(m_languageItem + 1);
				if(m_languageItem >= sizeof(LanguageEnum))
				{
					m_languageItem = static_cast<LanguageEnum>(0);
				}
				break;
			case VK_RETURN:
				switch(m_languageItem)
				{
					case LanguageEnum::E_EN:
					{
						mainWindow().getSettingsManager().setLanguage(E_EN);
						mainWindow().getDictionnary().setDefaultLanguage(E_EN);
						mainWindow().popController();
					}
					break;
					case LanguageEnum::E_FR:
					{
						mainWindow().getSettingsManager().setLanguage(E_FR);
						mainWindow().getDictionnary().setDefaultLanguage(E_FR);
						mainWindow().popController();
					}
					break;
				}
				break;
		}
	}

	void ControllerLanguages::paintScene() const
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(100.0f, 100.0f);
		getMainWindow().getPaintHelper().drawText("LANGUAGES");

		glColor3f(1.0f, m_languageItem == LanguageEnum::E_EN?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 200.0f);
		getMainWindow().getPaintHelper().drawText("English");

		glColor3f(1.0f, m_languageItem == LanguageEnum::E_FR?1.0f:0.0f, 0.0f);
		glRasterPos2f(100.0f, 300.0f);
		getMainWindow().getPaintHelper().drawText("Francais");
	}
}