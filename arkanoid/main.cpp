#include <memory>
#include <Windows.h>
#include <gl/GL.h>
#include "Window.h"

class MainWindow : public arkanoid::Window
{
	public:
	MainWindow(unsigned int p_width, unsigned int p_height, const std::string& p_title)
		: arkanoid::Window(p_width, p_height, p_title)
	{
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	virtual void paintScene() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glPushMatrix();
		glTranslatef(100.0f, 100.0f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		glVertex3f(100.0f, 100.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		glEnd();

		glPopMatrix();
	}

	virtual void onResize(unsigned int p_width, unsigned int p_height)
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

	virtual void onKeyDown(int p_virtualKey)
	{
	}

	virtual void onKeyUp(int p_virtualKey)
	{
	}
};

int WINAPI WinMain(HINSTANCE p_instance, HINSTANCE p_previousInstance, LPSTR p_args, int p_show)
{
	arkanoid::Window::registerClass();
	MainWindow* window(new MainWindow(800, 600, "Arkanoid"));
	window->show();

	// Event loop
	MSG message;
	bool run = true;
	while(run)
	{
		if(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
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
		else
		{
			window->paint();
		}
	}

	delete window;
	arkanoid::Window::unregisterClass();
}
