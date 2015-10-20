#include <chrono>
#include <thread>
#include <array>
#include <map>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <GL/GL.h>

#include "Cube.hpp"

#if defined _MSC_VER && _MSC_VER >= 1900
	#define CPP_14 1
#else
	#define CPP_14 0
#endif

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

#define VERTICAL_FOV 72.f

#define NEAR_PLANE 1.f
#define FAR_PLANE 10.f

#define CUBE_HALF_DIM 0.5

// milliseconds
#define FRAME_TIME 16

#if CPP_14
	constexpr int windowSize[] = {WIN_SIZE_X, WIN_SIZE_Y};	// x, y
	constexpr float aspectRatio = static_cast<float>(windowSize[0]) / windowSize[1];
	constexpr float vertFov = VERTICAL_FOV * 3.14159265359f / 180.f;

	constexpr float nearPlane = NEAR_PLANE;
	constexpr float farPlane = FAR_PLANE;

	constexpr const char* className = "myWindowClass";

	constexpr std::chrono::milliseconds frameTime{FRAME_TIME};
#else
	const int windowSize[] = {WIN_SIZE_X, WIN_SIZE_Y};	// x, y
	const float aspectRatio = static_cast<float>(windowSize[0]) / windowSize[1];
	const float vertFov = VERTICAL_FOV * 3.14159265359 / 180.f;

	const float nearPlane = NEAR_PLANE;
	const float farPlane = FAR_PLANE;

	const char* className = "myWindowClass";

	const std::chrono::milliseconds frameTime{FRAME_TIME};
#endif

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

	glViewport(0, 0, windowSize[0], windowSize[1]);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

//	MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

	Cube cube1(1.f);
	Cube cube2(1.5f);

	cube1.setPosition(-1.f, 0.5f, 0.f);
	cube2.setPosition(1.5f, -0.5f, -0.5f);

	cube1.setColor(0, {1.f, 0.f, 0.f, 0.5f});
	cube1.setColor(1, {0.f, 1.f, 0.f, 0.5f});
	cube1.setColor(2, {0.f, 0.f, 1.f, 0.5f});
	cube1.setColor(3, {1.f, 1.f, 1.f, 0.5f});
	cube1.setColor(4, {1.f, 1.f, 1.f, 0.5f});
	cube1.setColor(5, {0.f, 0.f, 1.f, 0.5f});
	cube1.setColor(6, {0.f, 1.f, 0.f, 0.5f});
	cube1.setColor(7, {1.f, 0.f, 0.f, 0.5f});

	cube2.setColor(0, {1.f, 0.f, 0.f, 1.f});
	cube2.setColor(1, {0.f, 1.f, 0.f, 1.f});
	cube2.setColor(2, {0.f, 0.f, 1.f, 1.f});
	cube2.setColor(3, {1.f, 1.f, 1.f, 1.f});
	cube2.setColor(4, {1.f, 1.f, 1.f, 1.f});
	cube2.setColor(5, {0.f, 0.f, 1.f, 1.f});
	cube2.setColor(6, {0.f, 1.f, 0.f, 1.f});
	cube2.setColor(7, {1.f, 0.f, 0.f, 1.f});

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

		cube1.setRotation(rotation, {1.f, 0.f, 0.f});
		cube1.setRotation(rotation, {0.f, 1.f, 0.f});
		cube1.setRotation(rotation, {0.f, 0.f, 1.f});

		cube2.setRotation(rotation, {1.f, 1.f, 1.f});

		// Drawing
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-widthHalf, widthHalf, -heightHalf, heightHalf, nearPlane, farPlane);

		glMatrixMode(GL_MODELVIEW);

		// move to center of the world
		cube1.draw({0.f, 0.f, -(farPlane - nearPlane + 1) / 2.f});

		// move to center of the world
		cube2.draw({0.f, 0.f, -(farPlane - nearPlane + 1) / 2.f});

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
