#include "Controller.h"
#include "MainWindow.h"

namespace arkanoid
{
	Controller::Controller(MainWindow& p_mainWindow)
		: m_mainWindow(p_mainWindow)
	{
	}

	Controller::~Controller()
	{
	}
}