#include <memory>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "MainWindow.h"

int WINAPI WinMain(HINSTANCE p_instance, HINSTANCE p_previousInstance, LPSTR p_args, int p_show)
{
	arkanoid::Window::registerClass();

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	{
		std::unique_ptr<arkanoid::MainWindow>window(new arkanoid::MainWindow(800, 600, "Arkanoid"));
		window->show();

		// Event loop
		MSG message;
		bool run = true;
		while(run)
		{
			while(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
			{
				if(message.message == WM_QUIT)
				{
					run = false;
					break;
				}
				else
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}

			window->animate();
			window->paint();

		//	std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//	Sleep(10);
		}
	}

	arkanoid::Window::unregisterClass();
}
