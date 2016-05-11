#include <Windows.h>
#include <gl/GL.h>

#define WINDOW_CLASS_NAME "OpenGL"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Arkanoid"
#define FRAMERATE_INTERVAL 30

void InitGl()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ResizeGl(int p_width, int p_height)
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

void DrawScene()
{
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

LRESULT	CALLBACK WndProc(HWND p_window, UINT p_message, WPARAM p_wParam, LPARAM p_lParam)
{
	switch(p_message)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			ResizeGl(LOWORD(p_lParam), HIWORD(p_lParam));
			return 0;
		case WM_KEYUP:
			// TODO
			return 0;
		case WM_KEYDOWN:
			// TODO
			return 0;
		default:
			return DefWindowProc(p_window, p_message, p_wParam, p_lParam);
	}
}

void KillWindow(HINSTANCE p_instance, HWND p_window, HDC p_deviceContext, HGLRC p_renderingContext)
{
	if(p_renderingContext)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(p_renderingContext);
	}

	if(p_deviceContext)
	{
		ReleaseDC(p_window, p_deviceContext);
	}

	if(p_window)
	{
		DestroyWindow(p_window);
	}

	UnregisterClass(WINDOW_CLASS_NAME, p_instance);
}

int WINAPI WinMain(HINSTANCE p_instance, HINSTANCE p_previousInstance, LPSTR p_args, int p_show)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    // Redraw on size, own DC window
	wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);   // Message callback
	wc.cbClsExtra = 0;                                // No extra window data
	wc.cbWndExtra = 0;                                // No extra window data
	wc.hInstance = p_instance;                        // Set the instance
	wc.hIcon = LoadIcon(0, IDI_WINLOGO);              // Load the default icon
	wc.hCursor = LoadCursor(0, IDC_ARROW);            // Load the arrow pointer
	wc.hbrBackground = 0;                             // No background required for OpenGL
	wc.lpszMenuName = 0;                              // No menu
	wc.lpszClassName = WINDOW_CLASS_NAME;             // Class name

	// Registering class.
	if(!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed to register the window class.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	RECT rect;
	rect.left = static_cast<long>(0);
	rect.right = static_cast<long>(WINDOW_WIDTH);
	rect.top = static_cast<long>(0);
	rect.bottom = static_cast<long>(WINDOW_HEIGHT);

	// Adjust desired rect to match screen area
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	// Create the window
	HWND hwnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,                         // Extended style
		WINDOW_CLASS_NAME,                                          // Class name
		WINDOW_TITLE,                               // Title
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,    // Style
		0, 0,                                                       // Position
		rect.right - rect.left,                                     // Width
		rect.bottom - rect.top,                                     // Height
		0,                                                          // No parent window
		0,                                                          // No menu
		p_instance,                                                 // Instance
		0                                                           // Nothing to pass to WM_CREATE
	);

	if(!hwnd)
	{
		KillWindow(p_instance, hwnd, 0, 0);
		MessageBox(NULL, "Unable to create window.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	// Retrieving device context
	HDC deviceContext = GetDC(hwnd);
	if(!deviceContext)
	{
		KillWindow(p_instance, hwnd, 0, 0);
		MessageBox(NULL, "Unable to create an OpenGL device context.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,                                                             // Version number
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Required features
		PFD_TYPE_RGBA,                                                 // RGBA Format
		32,                                                            // Color depth
		0, 0, 0, 0, 0, 0,                                              // Color bits ignored
		0,                                                             // No alpha buffer
		0,                                                             // Shift bit ignored
		0,                                                             // No accumulation buffer
		0, 0, 0, 0,                                                    // Accumulation bits ignored
		16,                                                            // 16bit Z-buffer (depth buffer)  
		0,                                                             // No stencil buffer
		0,                                                             // No auxiliary buffer
		PFD_MAIN_PLANE,                                                // Main drawing layer
		0,
		0, 0, 0                                                        // Layer masks ignored
	};

	// Retrieving pixel format
	int pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
	if(!pixelFormat)
	{
		KillWindow(p_instance, hwnd, deviceContext, 0);
		MessageBox(NULL, "Unable to find a suitable pixel format.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	// Setting pixel format
	if(!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDescriptor))
	{
		KillWindow(p_instance, hwnd, deviceContext, 0);
		MessageBox(NULL, "Unable to set the pixel format.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	// Creating rendering context
	HGLRC renderingContext = wglCreateContext(deviceContext);
	if(!renderingContext)
	{
		KillWindow(p_instance, hwnd, deviceContext, 0);
		MessageBox(NULL, "Unable to create an OpenGL rendering context.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	// Activating rendering context
	if(!wglMakeCurrent(deviceContext, renderingContext))
	{
		KillWindow(p_instance, hwnd, deviceContext, renderingContext);
		MessageBox(NULL, "Unable to activate the OpenGL rendering context.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);    // Showing window
	SetForegroundWindow(hwnd);    // Set to foreground
	SetFocus(hwnd);               // Grab keyboard focus

	InitGl();

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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			DrawScene();

			SwapBuffers(deviceContext);
		}
	}

	KillWindow(p_instance, hwnd, deviceContext, renderingContext);

	return message.wParam;
}
