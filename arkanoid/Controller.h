#ifndef ARKANOID_CONTROLLER_H
#define ARKANOID_CONTROLLER_H

namespace arkanoid { class MainWindow; }

namespace arkanoid
{
	class Controller
	{
		private:
		MainWindow& m_mainWindow;

		public:
		Controller(MainWindow& p_mainWindow);
		virtual ~Controller();

		inline const MainWindow& getMainWindow() const;
		inline MainWindow& mainWindow();

		virtual void onKeyDown(int p_virtualKey) = 0;
		virtual void onKeyUp(int p_virtualKey) = 0;
		virtual void animate() {}
		virtual void paintScene() const = 0;
	};
}

namespace arkanoid
{
	const MainWindow& Controller::getMainWindow() const
	{
		return m_mainWindow;
	}

	MainWindow& Controller::mainWindow()
	{
		return m_mainWindow;
	}
}

#endif
