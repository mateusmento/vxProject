#include <vix\internal\OpenGL.h>
#include <vix\internal\Window.h>


VIX_CODE_BEGIN


static vxGLContext* current;

VIX_API
vxGLContext* vxOpenGL_createContext(vxWindow* window)
{
	verify(window, "Passing a null vxWindow* to " __FUNCTION__);
	HDC hdc = GetDC(window->handle);
	vxGLContext* glcontext = (vxGLContext*)malloc(sizeof(vxGLContext));
	glcontext->handle = wglCreateContext(hdc);
	glcontext->isbond = false;
	ReleaseDC(window->handle, hdc);
	return glcontext;
}

VIX_API
void vxOpenGL_deleteContext(vxGLContext* glcontext)
{
	if (!glcontext) return;

	if (glcontext->isbond) wglMakeCurrent(NULL, NULL);
	wglDeleteContext(glcontext->handle);
	free(glcontext);
}

VIX_API
void vxOpenGL_bindContext(vxGLContext* glcontext, vxWindow* window)
{
	verify(window, "Passing a null vxWindow* to " __FUNCTION__);
	verify(glcontext, "Passing a null vxGLContext* to " __FUNCTION__);
	
	if (!glcontext->isbond) {
		HDC hdc = GetDC(window->handle);
		verify(wglMakeCurrent(hdc, glcontext->handle), "fail to make opengl context current");
		glcontext->isbond = true;
		ReleaseDC(window->handle, hdc);
	}
}

VIX_API
void vxOpenGL_unbindContext(vxGLContext* glcontext)
{
	verify(glcontext, "Passing a null vxGLContext* to " __FUNCTION__);
	if (glcontext->isbond) {
		wglMakeCurrent(NULL, NULL);
		glcontext->isbond = false;
	}
}

VIX_API
vxWindow* vxOpenGL_getCurrentContext()
{
	HDC hdc = wglGetCurrentDC();
	HWND hwnd = WindowFromDC(hdc);
	vxWindow* window = (vxWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	return window;
}


VIX_CODE_END

