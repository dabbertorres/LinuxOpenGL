#ifdef _WIN32

#include "Window.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static constexpr const wchar_t* className = L"SwiftWindow";

static LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static void registerClass();

Window::Window()
{}

Window::~Window()
{}

static LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:

			break;

		case WM_CLOSE:
			// don't forward close message so OS doesn't automatically destroy the window
			return 0;

		case WM_SYSCOMMAND:
			// don't forward the menu system command, so that pressing ALT or F10 doesn't steal the focus
			if(wParam == SC_KEYMENU)
				return 0;

		default:
			break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

static void registerClass()
{
	WNDCLASSEXW windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEXW);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = &messageHandler;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleW(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = NULL;

	RegisterClassExW(&windowClass);
}

#endif
