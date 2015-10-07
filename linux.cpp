#include <iostream>

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

int main(int argc, char** argv)
{
	Display* display;
	Window root;
	// color depth, depth size: 24 bits, use double buffer, "None" terminates the list
	GLint attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
	XVisualInfo* visualInfo;
	Colormap colorMap;
	XSetWindowAttributes setWindowAttributes;
	Window window;
	GLXContext context;
	XWindowAttributes windowAttributes;
	XEvent event;
	bool running = true;

	// 0 means local machine
	display = XOpenDisplay(0);

	if(display == nullptr)
	{
		std::cerr << "Cannot connect to X server\n";
		return 1;
	}

	// root is desktop "window"
	root = DefaultRootWindow(display);

	visualInfo = glXChooseVisual(display, 0 , attributes);

	if(visualInfo == nullptr)
	{
		std::cerr << "No appropriate visual setting found.\n";
		return 2;
	}
	else
	{
		std::cout << "Selected visual: " << visualInfo->visualid << '\n';
	}

	colorMap = XCreateColormap(display, root, visualInfo->visual, AllocNone);

	setWindowAttributes.colormap = colorMap;
	setWindowAttributes.event_mask = ExposureMask | KeyPressMask;

	// display to create window on, parent window, x position, y position, width, height, border width, depth, window type, set values for attributes
	window = XCreateWindow(display, root, 0, 0, 800, 600, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &setWindowAttributes);

	XMapWindow(display, window);
	XStoreName(display, window, "X Window for OpenGL");

	context = glXCreateContext(display, visualInfo, 0, GL_TRUE);	// true if on local machine
	glXMakeCurrent(display, window, context);

	glEnable(GL_DEPTH_TEST);

	while(running)
	{
		XNextEvent(display, &event);

		switch(event.type)
		{
			case Expose:
				XGetWindowAttributes(display, window, &windowAttributes);
				glViewport(0, 0, windowAttributes.width, windowAttributes.height);
				break;

			case KeyPress:
				running = false;
				break;

			default:
				break;
		}

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glXSwapBuffers(display, window);
	}

	// detach context
	glXMakeCurrent(display, None, 0);

	// clean up
	glXDestroyContext(display, context);
	XDestroyWindow(display, window);
	XCloseDisplay(display);

	return 0;
}
