#ifndef ARKANOID_WINDOW_H
#define ARKANOID_WINDOW_H

#include <stdexcept>
#include <string>
#include <Windows.h>

namespace arkanoid
{
	class Window
	{
		public:
		static void registerClass() throw (std::runtime_error);
		static void unregisterClass();

		private:
		HWND m_handle;
		HDC m_deviceContext;
		HGLRC m_renderingContext;

		public:
		Window(unsigned int p_width, unsigned int p_height, const std::string& p_title) throw (std::runtime_error);
		virtual ~Window();

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void show() const;
		void paint() const;

		virtual void onResize(unsigned int p_width, unsigned int p_height) = 0;
		virtual void onKeyDown(int p_virtualKey) = 0;
		virtual void onKeyUp(int p_virtualKey) = 0;

		protected:
		virtual void paintScene() const = 0;

		private:
		void cleanup();
	};
}

LRESULT	CALLBACK WndProc(HWND p_window, UINT p_message, WPARAM p_wParam, LPARAM p_lParam);

#endif