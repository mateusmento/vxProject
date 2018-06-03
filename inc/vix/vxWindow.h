#pragma once
#include "vxBase.h"

VIX_CODE_BEGIN

struct vxIWindow
{
	const bool isopen;
	const char* const title;
	const vxRect rect;
	const int width, height;
	void* userdata;
	vxGLContext* const glcontext;
};

#define vxWindow_interface(window) cast(vxIWindow*, window)
#define vxWindow_isOpen(window) cast(const bool, cast(vxIWindow*, window)->isopen)
#define vxWindow_rect(window) cast(const vxRect, cast(vxIWindow*, window)->rect)
#define vxWindow_width(window) cast(const int, cast(vxIWindow*, window)->width)
#define vxWindow_height(window) cast(const int, cast(vxIWindow*, window)->height)
#define vxWindow_glcontext(window) cast(const vxGLContext*, cast(vxIWindow*, window)->glcontext)

VIX_API vxWindow* vxWindow_new();
VIX_API void vxWindow_delete(vxWindow* window);

VIX_API void vxWindow_open(vxWindow* window, const char* title, int x, int y, int width, int height);
VIX_API void vxWindow_close(vxWindow* window);

VIX_API void vxWindow_supportOpenGL(vxWindow* window);


VIX_CODE_END
