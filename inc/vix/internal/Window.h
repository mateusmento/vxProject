#pragma once
#include "../vxWindow.h"
#include <Windows.h>

VIX_CODE_BEGIN

struct vxWindow
{
	bool isopen;
	const char* title;
	vxRect rect;
	int width, height;
	void* userData;
	vxGLContext* glcontext;

//internal:
	HWND handle;
	int pixelFormat;
};

VIX_API void vxWindow_zero(vxWindow* window);

VIX_CODE_END