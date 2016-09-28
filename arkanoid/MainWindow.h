#ifndef ARKANOID_MAIN_WINDOW_H
#define ARKANOID_MAIN_WINDOW_H

#include <stack>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Window.h"
#include "PaintHelper.h"

namespace arkanoid { class Controller; }

namespace arkanoid
{
	class MainWindow : public arkanoid::Window
	{
		private:
		PaintHelper m_paintHelper;
		std::stack<Controller*> m_controllers;

		public:
		MainWindow(unsigned int p_width, unsigned int p_height, const std::string& p_title);
		~MainWindow();

		inline const PaintHelper& getPaintHelper() const;

		void pushController(Controller* p_controller);
		void popController();

		void animate();

		virtual void paintScene() const;
		virtual void onResize(unsigned int p_width, unsigned int p_height);
		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
	};
}

namespace arkanoid
{
	const PaintHelper& MainWindow::getPaintHelper() const
	{
		return m_paintHelper;
	}
}

#endif
