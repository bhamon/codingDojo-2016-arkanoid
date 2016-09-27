#ifndef ARKANOID_MAIN_WINDOW_H
#define ARKANOID_MAIN_WINDOW_H

#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Window.h"
#include "PaintHelper.h"
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Game.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Player.h>
#include <arkanoid-model\Racket.h>

namespace arkanoid
{
	class MainWindow : public arkanoid::Window
	{
		private:
		PaintHelper m_paintHelper;
		Ball m_ball;
		Racket m_racket;
		Field m_field;
		Player m_player;
		Game m_game;
		bool m_goLeft;
		bool m_goRight;

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
