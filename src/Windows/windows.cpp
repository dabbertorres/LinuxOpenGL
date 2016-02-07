#include <chrono>
#include <thread>
#include <array>
#include <map>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "gl_glCore33.hpp"

using namespace dbr;
using namespace std::chrono_literals;

constexpr int windowSize[] = {800, 600};	// x, y
constexpr float aspectRatio = static_cast<float>(windowSize[0]) / windowSize[1];
constexpr float vertFov = 72 * 3.14159265359f / 180.f;

constexpr float nearPlane = 1.f;
constexpr float farPlane = 11.f;

constexpr const char* className = "myWindowClass";

constexpr auto frameTime = 16ms;

const float tangent = std::tanf(vertFov / 2.f);
const float heightHalf = nearPlane * tangent;
const float widthHalf = heightHalf * aspectRatio;

bool isOpen = true;

LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int argc, char** argv);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	return main(__argc, __argv);
}

int main(int argc, char** argv)
{
	WNDCLASSEX windowClass;

	// Register the Window Class
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = messageHandler;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = NULL;
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
		return 1;
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

	HWND windowHandle = CreateWindowEx(WS_EX_CLIENTEDGE, className, "Windoze OpenGL", WS_OVERLAPPEDWINDOW,
									   CW_USEDEFAULT, CW_USEDEFAULT, windowSize[0], windowSize[1], NULL, NULL, NULL, NULL);

	// make sure window was created
	if(windowHandle == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 2;
	}

	HDC deviceContext = GetDC(windowHandle);

	int pixelFormatID = ChoosePixelFormat(deviceContext, &pfd);

	if(pixelFormatID == 0)
	{
		MessageBox(NULL, "Pixel Format selection failed.", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 3;
	}

	if(!SetPixelFormat(deviceContext, pixelFormatID, &pfd))
	{
		MessageBox(NULL, "Pixel Format setting failed.", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 4;
	}

	// OpenGL context stuff
	HGLRC glContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, glContext);

	// load OpenGL functions
	if(!gl::sys::LoadFunctions())
	{
		// ah!!!
	}

	gl::Viewport(0, 0, windowSize[0], windowSize[1]);

	gl::ClearColor(0.f, 0.f, 0.f, 1.f);

//	MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

	float rotation = 0;

	// start!
	ShowWindow(windowHandle, SW_SHOWNORMAL);
	UpdateWindow(windowHandle);

	while(isOpen)
	{
		auto start = std::chrono::system_clock::now().time_since_epoch();

		// Events
		MSG msg;
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Drawing
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		
		SwapBuffers(deviceContext);

		rotation += 1;
		rotation = std::fmod(rotation, 360.f);

		auto end = std::chrono::system_clock::now().time_since_epoch();

		// keep a framerate
		auto toSleepFor = end - start - frameTime;
		if(toSleepFor < std::chrono::milliseconds::zero())
			std::this_thread::sleep_for(toSleepFor * -1);
	}

	// cleanup
	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(glContext);

	return 0;
}

LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			isOpen = false;
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			isOpen = false;
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}
