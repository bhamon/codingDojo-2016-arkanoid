#ifndef ARKANOID_MAIN_WINDOW_H
#define ARKANOID_MAIN_WINDOW_H

#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <arkanoid-model\Ball.h>
#include <arkanoid-model\Brick.h>
#include <arkanoid-model\Game.h>
#include <arkanoid-model\Field.h>
#include <arkanoid-model\Player.h>
#include <arkanoid-model\Racket.h>

namespace arkanoid
{
	class GameEngine
	{
		private:
			GLUquadric* m_quadric;
			Ball m_ball;
			Racket m_racket;
			Field m_field;
			Player m_player;
			Game m_game;
			bool m_goLeft;
			bool m_goRight;

		public:

			GameEngine();
			~GameEngine();

			void animate();

			void paintScene() const;
			void onResize(unsigned int p_width, unsigned int p_height);
			void onKeyDown(int p_virtualKey);
			void onKeyUp(int p_virtualKey);
	};
}

#endif
