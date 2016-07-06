#ifndef ARKANOID_MAIN_WINDOW_H
#define ARKANOID_MAIN_WINDOW_H

#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Window.h"
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Brick.h>

namespace arkanoid
{
	class MainWindow : public arkanoid::Window
	{
		private:
		GLuint m_font;
		GLUquadric* m_quadric;
		Ball m_ball;
		std::vector<Brick> m_bricks;

		public:
		MainWindow(unsigned int p_width, unsigned int p_height, const std::string& p_title);
		~MainWindow();

		void animate();

		virtual void paintScene() const;
		virtual void onResize(unsigned int p_width, unsigned int p_height);
		virtual void onKeyDown(int p_virtualKey);
		virtual void onKeyUp(int p_virtualKey);
	};
}

#endif
