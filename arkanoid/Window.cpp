#include "Window.h"
#include <map>

#define WINDOW_CLASS_NAME "OpenGL"

static std::map<HWND, arkanoid::Window*> s_windows;

namespace arkanoid
{
	void
	Window::registerClass()
	{
		HINSTANCE instance = GetModuleHandle(0);

		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    // Redraw on size, own DC window
		wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);   // Message callback
		wc.cbClsExtra = 0;                                // No extra window data
		wc.cbWndExtra = 0;                                // No extra window data
		wc.hInstance = instance;                          // Set the instance
		wc.hIcon = LoadIcon(0, IDI_WINLOGO);              // Load the default icon
		wc.hCursor = LoadCursor(0, IDC_ARROW);            // Load the arrow pointer
		wc.hbrBackground = 0;                             // No background required for OpenGL
		wc.lpszMenuName = 0;                              // No menu
		wc.lpszClassName = WINDOW_CLASS_NAME;             // Class name

		// Registering class.
		if(!RegisterClass(&wc))
		{
			throw std::runtime_error("Failed to register the window class");
		}
	}

	void
	Window::unregisterClass()
	{
		HINSTANCE instance = GetModuleHandle(0);
		UnregisterClass(WINDOW_CLASS_NAME, instance);
	}

	Window::Window(unsigned int p_width, unsigned int p_height, const std::string& p_title)
		: m_handle(0)
		, m_deviceContext(0)
		, m_renderingContext(0)
	{
		HINSTANCE instance = GetModuleHandle(0);

		RECT rect;
		rect.left = static_cast<long>(0);
		rect.right = static_cast<long>(p_width);
		rect.top = static_cast<long>(0);
		rect.bottom = static_cast<long>(p_height);

		// Adjust desired rect to match screen area
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		// Create the window
		m_handle = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,                         // Extended style
			WINDOW_CLASS_NAME,                                          // Class name
			p_title.c_str(),                                            // Title
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,    // Style
			0, 0,                                                       // Position
			rect.right - rect.left,                                     // Width
			rect.bottom - rect.top,                                     // Height
			0,                                                          // No parent window
			0,                                                          // No menu
			instance,                                                   // Instance
			0                                                           // Nothing to pass to WM_CREATE
		);

		if(!m_handle)
		{
			cleanup();
			throw std::runtime_error("Unable to create window");
		}

		// Retrieving device context
		m_deviceContext = GetDC(m_handle);
		if(!m_deviceContext)
		{
			cleanup();
			throw std::runtime_error("Unable to create an OpenGL device context");
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
		int pixelFormat = ChoosePixelFormat(m_deviceContext, &pixelFormatDescriptor);
		if(!pixelFormat)
		{
			cleanup();
			throw std::runtime_error("Unable to find a suitable pixel format");
		}

		// Setting pixel format
		if(!SetPixelFormat(m_deviceContext, pixelFormat, &pixelFormatDescriptor))
		{
			cleanup();
			throw std::runtime_error("Unable to set the pixel format");
		}

		// Creating rendering context
		m_renderingContext = wglCreateContext(m_deviceContext);
		if(!m_renderingContext)
		{
			cleanup();
			throw std::runtime_error("Unable to create an OpenGL rendering context");
		}

		// Activating rendering context
		if(!wglMakeCurrent(m_deviceContext, m_renderingContext))
		{
			cleanup();
			throw std::runtime_error("Unable to activate the OpenGL rendering context");
		}

		s_windows[m_handle] = this;
	}

	Window::~Window()
	{
		cleanup();
		s_windows.erase(m_handle);
	}

	unsigned int Window::getWidth() const
	{
		RECT rect;
		GetWindowRect(m_handle, &rect);
		return rect.right - rect.left;
	}

	unsigned int Window::getHeight() const
	{
		RECT rect;
		GetWindowRect(m_handle, &rect);
		return rect.bottom - rect.top;
	}

	void
	Window::show() const
	{
		ShowWindow(m_handle, SW_SHOW);    // Showing window
		SetForegroundWindow(m_handle);    // Set to foreground
		SetFocus(m_handle);               // Grab keyboard focus
	}

	void
	Window::paint() const
	{
		paintScene();
		SwapBuffers(m_deviceContext);
	}

	void
	Window::cleanup()
	{
		if(m_renderingContext)
		{
			wglMakeCurrent(0, 0);
			wglDeleteContext(m_renderingContext);
		}

		if(m_deviceContext)
		{
			ReleaseDC(m_handle, m_deviceContext);
		}

		if(m_handle)
		{
			DestroyWindow(m_handle);
		}
	}
}

LRESULT	CALLBACK WndProc(HWND p_window, UINT p_message, WPARAM p_wParam, LPARAM p_lParam)
{
	auto it = s_windows.find(p_window);
	if(it == s_windows.end())
	{
		return DefWindowProc(p_window, p_message, p_wParam, p_lParam);
	}

	arkanoid::Window* window = it->second;
	switch(p_message)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			window->onResize(LOWORD(p_lParam), HIWORD(p_lParam));
			return 0;
		case WM_KEYUP:
			window->onKeyUp(p_wParam);
			return 0;
		case WM_KEYDOWN:
			window->onKeyDown(p_wParam);
			return 0;
		default:
			return DefWindowProc(p_window, p_message, p_wParam, p_lParam);
	}
}