#include <iostream>

#include <windows.h>
#include <GL/GL.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*int main(int argc, char** argv)
{
	return 0;
}*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	constexpr const char* className = "myWindowClass";

	// Register the Window Class
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
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

	HWND windowHandle = CreateWindowEx(WS_EX_CLIENTEDGE, className, "Windoze...", WS_OVERLAPPEDWINDOW, 
										CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL);
	
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
	
	// OpenGL
	HGLRC glContext = wglCreateContext(deviceContext);
	
	wglMakeCurrent(deviceContext, glContext);

	// start!
	ShowWindow(windowHandle, nCmdShow);
	UpdateWindow(windowHandle);
	
	MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

	// Message Loop
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	wglMakeCurrent(NULL, NULL);
	
	wglDeleteContext(glContext);

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
