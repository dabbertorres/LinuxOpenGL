#include "Window.hpp"

#include <stdexcept>

static constexpr const char* className = "dbr::gl";

static LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static void registerClass();

namespace dbr
{
	namespace gl
	{
		namespace windows
		{
			bool Window::classRegistered = false;

			Window::Window(std::size_t width, std::size_t height)
			{
				// make sure we register the Window class once
				if(!classRegistered)
				{
					registerClass();
					classRegistered = true;
				}

				PIXELFORMATDESCRIPTOR pfd =
				{
					sizeof(PIXELFORMATDESCRIPTOR),
					1,
					PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,	// Flags
					PFD_TYPE_RGBA,		// The kind of framebuffer. RGBA or palette.
					32,					// Colordepth of the framebuffer.
					0, 0, 0, 0, 0, 0,
					0,
					0,
					0,
					0, 0, 0, 0,
					24,					// Number of bits for the depthbuffer
					8,					// Number of bits for the stencilbuffer
					0,					// Number of aux buffers in the framebuffer.
					PFD_MAIN_PLANE,
					0,
					0, 0, 0
				};

				handle = CreateWindowEx(WS_EX_CLIENTEDGE, className, "Windoze OpenGL", WS_OVERLAPPEDWINDOW,
												   CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, NULL, NULL);

				// make sure window was created
				if(handle == NULL)
				{
					MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
					throw std::runtime_error("Failed to create a window");
				}

				deviceContext = GetDC(handle);

				int pixelFormatID = ChoosePixelFormat(deviceContext, &pfd);

				if(pixelFormatID == 0)
				{
					MessageBox(NULL, "Pixel Format selection failed.", "Error!", MB_ICONEXCLAMATION | MB_OK);
					throw std::runtime_error("Pixel Format selection failed");
				}

				if(!SetPixelFormat(deviceContext, pixelFormatID, &pfd))
				{
					MessageBox(NULL, "Pixel Format setting failed.", "Error!", MB_ICONEXCLAMATION | MB_OK);
					throw std::runtime_error("Pixel Format setting failed");
				}

				ShowWindow(handle, SW_SHOWNORMAL);
				UpdateWindow(handle);
			}

			Window::~Window()
			{}

			bool Window::isOpen()
			{
				return false;
			}

			void Window::close()
			{

			}
		}
	}
}

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
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = messageHandler;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleW(NULL);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// make sure window class is valid
	if(!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	}
}
