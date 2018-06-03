#include <vix\internal\Window.h>
#include <vix\internal\OpenGL.h>

#include "WndProc.h"


VIX_CODE_BEGIN


// TODO: define a OpenGLWindow
// TODO: define a default contructor for vxWindow
VIX_API
void vxWindow_zero(vxWindow* window)
{
	window->isopen = false;
	window->handle = null;
//	window->glcontext = null;
	window->pixelFormat = 0;
}

VIX_API
vxWindow* vxWindow_new()
{
	vxWindow* window = (vxWindow*) malloc(sizeof(vxWindow));
	vxWindow_zero(window);
	return window;
}

VIX_API
void vxWindow_delete(vxWindow* window)
{
	verify(window, "Passing a null vxWindow* to " __FUNCTION__);
	if (window->isopen)
		vxWindow_close(window);
	free(window);
}

VIX_API
void vxWindow_open(vxWindow* window, const char* title, int x, int y, int width, int height)
{
	verify(window, "Passing a null vxWindow* to " __FUNCTION__);

	static HINSTANCE hInstance = null;
	const char * const WINDOW_CLASS = "vxWindow";

	if (!hInstance)
	{
		hInstance = GetModuleHandle(null);
		WNDCLASS wc = { 0 };
		wc.hInstance = hInstance;
		wc.lpszClassName = WINDOW_CLASS;
		wc.lpfnWndProc = WndProc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXCLAMATION));
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);
	}
	
	HWND hwnd = CreateWindow(WINDOW_CLASS, title, WS_OVERLAPPEDWINDOW, x, y, width, height, null, null, hInstance, window);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

VIX_API
void vxWindow_close(vxWindow* window)
{
	verify(window, "Passing a null vxWindow* to " __FUNCTION__);
	if (!window->isopen) return;

//	if (window->glcontext) vxOpenGL_deleteContext(window->glcontext);
	DestroyWindow(window->handle);

	vxWindow_zero(window);
}

VIX_API
void vxWindow_supportOpenGL(vxWindow* window)
{
	HDC hdc = GetDC(window->handle);

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	ReleaseDC(window->handle, hdc);
}


VIX_CODE_END