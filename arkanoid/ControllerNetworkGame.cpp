#include "ControllerNetworkGame.h"

#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <sstream>

#include "arkanoid-model/MultiPlayerGame.h"
#include "arkanoid-model/TrameInit.h"
#include "arkanoid-model/TrameDiff.h"
#include "MainWindow.h"

#define BUFF_LEN 512


namespace arkanoid
{

	ControllerNetworkGame::ControllerNetworkGame(MainWindow& p_mainWindow, std::istream& file, const std::string& port)
		: ControllerGame(p_mainWindow, file, new MultiPlayerGame())
		, m_serverSocket(INVALID_SOCKET)
		, m_player2("joueur 2")
		, m_racket2(math::Point2<float>(200.f, Racket::OFFSET))
		, m_goLeft2(false)
		, m_goRight2(false)
	{
		MultiPlayerGame* pMultiPlayerGame = getGame();
		pMultiPlayerGame->setPlayer2(&m_player2);
		pMultiPlayerGame->setRacket2(&m_racket2);

		m_ssThread = std::thread([&]() {
			struct addrinfo *result = NULL, *ptr = NULL, hints;

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
			hints.ai_flags = AI_PASSIVE;

			getaddrinfo(NULL, port.c_str(), &hints, &result);
			m_serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			bind(m_serverSocket, result->ai_addr, (int)result->ai_addrlen);
			listen(m_serverSocket, SOMAXCONN);

			// XD
			Sleep(2000);

			SOCKET clientSocket = INVALID_SOCKET;
			clientSocket = accept(m_serverSocket, static_cast<sockaddr*>(NULL), static_cast<int*>(NULL));

			char recvbuf[BUFF_LEN];
			int iResult, iSendResult;
			int recvbuflen = BUFF_LEN;

			char buffer[4096];
			size_t size;


			network::TrameInit trameInit(*pMultiPlayerGame->getField());
			size = trameInit.serialize(buffer);
			send(clientSocket, buffer, size, 0); // init packet

			network::TrameDiff::listTupleII brickInfo;
			network::TrameDiff tramediff(*pMultiPlayerGame->getBall(), brickInfo, *pMultiPlayerGame->getRacket(), m_racket2);
			size = tramediff.serialize(buffer);
			send(clientSocket, buffer, size, 0); // init packet

			do
			{
				iResult = recv(clientSocket, recvbuf, recvbuflen, 0);

				if(iResult > 0)
				{

					iSendResult = send(clientSocket, recvbuf, iResult, 0); // echo server
				}
			} while(iResult > 0);
		});
	}

	ControllerNetworkGame::~ControllerNetworkGame()
	{
		m_ssThread.join();
	}

	void ControllerNetworkGame::animate()
	{
		if (gameIsFinished() == false)
		{
			if (m_goLeft2)
			{
				m_racket2.position().setX(m_racket2.position().getX() - 0.2f);
			}

			if (m_goRight2)
			{
				m_racket2.position().setX(m_racket2.position().getX() + 0.2f);
			}
		}
		ControllerGame::animate();
	}

	void ControllerNetworkGame::paintScene() const
	{
		ControllerGame::paintScene();

		glColor3f(1.0f, 1.0f, 0.0f);

		glRasterPos2f(650.0f, 150.0f);
		std::ostringstream ost;
		ost << "score: " << m_player2.getScore();
		getMainWindow().getPaintHelper().drawText(ost.str());

		ost.str("");
		ost << getMainWindow().getDictionnary().translate(Dictionnary::E_LIFE) << ": " << m_player2.getLives();
		glRasterPos2f(900.0f, 150.0f);
		getMainWindow().getPaintHelper().drawText(ost.str());

		glPushMatrix();
		{
			glTranslatef(100.0f, 100.0f, 0.0f);

			glPushMatrix();
			{
				glTranslatef(0.0f, 100.0f, 0.0f);

				drawRacket(m_racket2);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	MultiPlayerGame* ControllerNetworkGame::getGame()
	{
		return dynamic_cast<MultiPlayerGame*>(ControllerGame::getGame());
	}
}