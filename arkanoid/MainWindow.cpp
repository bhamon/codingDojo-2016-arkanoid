#include "MainWindow.h"
#include "Controller.h"
#include "ControllerMenu.h"

namespace arkanoid
{
	MainWindow::MainWindow(unsigned int p_width, unsigned int p_height, const std::string& p_title)
		: arkanoid::Window(p_width, p_height, p_title)
		, m_paintHelper(m_deviceContext)
		, m_controllers()
	{
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		m_controllers.push(new ControllerMenu(*this));
	}

	MainWindow::~MainWindow()
	{
		while(m_controllers.size())
		{
			delete m_controllers.top();
			m_controllers.pop();
		}
	}

	void MainWindow::pushController(Controller* p_controller)
	{
		m_controllers.push(p_controller);
	}

	void MainWindow::popController()
	{
		if(m_controllers.size() == 0)
		{
			return;
		}

		delete m_controllers.top();
		m_controllers.pop();
	}

	void MainWindow::animate()
	{
		m_controllers.top()->animate();
	}

	void MainWindow::paintScene() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		m_controllers.top()->paintScene();
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
		m_controllers.top()->onKeyDown(p_virtualKey);
	}

	void MainWindow::onKeyUp(int p_virtualKey)
	{
		m_controllers.top()->onKeyUp(p_virtualKey);
	}

	SettingsManager& MainWindow::getSettingsManager()
	{
		return m_settingsManager;
	}

	Dictionnary& MainWindow::getDictionnary()
	{
		return m_dict;
	}

	const Dictionnary& MainWindow::getDictionnary() const
	{
		return m_dict;
	}
};