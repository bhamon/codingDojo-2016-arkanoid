#ifndef ARKANOID_CONTROLLER_NETWORK_GAME_H
#define ARKANOID_CONTROLLER_NETWORK_GAME_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <thread>
#include "ControllerGame.h"

class MultiPlayerGame;

namespace arkanoid
{
	class ControllerNetworkGame : public ControllerGame
	{
	public:
		ControllerNetworkGame(MainWindow& p_mainWindow, std::istream& file, const std::string& port);
		virtual ~ControllerNetworkGame();

		virtual void animate();
		virtual void paintScene() const;
		
	private:
		MultiPlayerGame* getGame();

		SOCKET m_serverSocket;
		std::thread m_ssThread;
		Player m_player2;
		Racket m_racket2;
		bool m_goLeft2;
		bool m_goRight2;
	};
}

#endif // !ARKANOID_CONTROLLER_MULTI_GAME_H
