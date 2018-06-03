#include <vix\vxBase.h>
#include <vix\vxWindow.h>
#include <vix\vxEvent.h>
#include <vix\vxOpenGL.h>

#include "main.h"
#include <Windows.h>

#include <gl\GL.h>
#include <gl\GLU.h>

bool running = true;
bool keepgoing = true;
bool insideThread = true;

vxGLContext* gl;
vxWindow* window1 = vxWindow_new();
vxWindow* window2 = vxWindow_new();


void draw(vxWindow* window)
{
	vxOpenGL_bindContext(gl, window);

	glViewport(0, 0, vxWindow_width(window), vxWindow_height(window));
	glClearColor(0, 0.2, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(40);
	glBegin(GL_POINTS);
	glColor3f(vxRandom_factor(), vxRandom_factor(), vxRandom_factor());
	glVertex2f(vxRandom_range(-1, 1), vxRandom_range(-1, 1));
	glEnd();
	glFlush();

	vxOpenGL_unbindContext(gl);
}


int main()
{
	vxWindow_open(window1, "Game 1", -100, 0, 640, 480);
//	vxWindow_open(window2, "Game 2", 100, 100, 480, 640);
	vxWindow_open(window2, "Game 2", 100, 100, 480, 640);

	vxEvent_func([](vxEvent* e)
	{
//		puts(vxEvent_name(e->type));

		switch (e->type)
		{
		case vxEvent_Quit:
			vxTimer_sleep(0);
			running = false;
			break;

		case vxEvent_WindowClose:
			vxWindow_close(e->window.window);
			break;

		case vxEvent_WindowBeginResizeMove:
			keepgoing = true;
			async([]() {
				insideThread = true;
				while (keepgoing) {
				}
				insideThread = false;
			});
			break;

		case vxEvent_WindowEndResizeMove:
			keepgoing = false;
			while (insideThread);
			break;
		}
	});


	while (running)
	{
		while (vxEvent_next());

	}
}

