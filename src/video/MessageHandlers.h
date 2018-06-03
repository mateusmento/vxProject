#pragma once
extern "C" {
	#include <vix\internal\Window.h>
	#include <vix\internal\Event.h>
	#include <vix\internal\OpenGL.h>
}

void createHandler(HWND hwnd, CREATESTRUCT* c);
void moveHandler(vxWindow* window, LPARAM lparam);
void resizeHandler(vxWindow* window);


void createHandler(HWND hwnd, CREATESTRUCT* c)
{
	RECT r = {0};
	AdjustWindowRect(&r, GetWindowLong(hwnd, GWL_STYLE), false);

	vxWindow* window = (vxWindow*)c->lpCreateParams;
	window->handle = hwnd;
	window->isopen = true;
	window->rect.x = c->x;
	window->rect.y = c->y;
	window->rect.width = c->cx + r.right - r.left;
	window->rect.height = c->cy + r.bottom - r.top;
	window->width = c->cx;
	window->height = c->cy;
	window->pixelFormat = 0;

	vxRect* a = &window->rect;
	SetWindowPos(hwnd, null, a->x, a->y, a->width, a->height, SWP_NOACTIVATE | SWP_NOZORDER);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)window);
}

void moveHandler(vxWindow* window, LPARAM lparam)
{
	RECT* r = (RECT*)lparam;
	window->rect.x = r->left;
	window->rect.y = r->top;
}

void resizeHandler(vxWindow* window)
{
	RECT rect;
	GetClientRect(window->handle, &rect);
	window->width = rect.right;
	window->height = rect.bottom;

	GetWindowRect(window->handle, &rect);
	window->rect.x = rect.left;
	window->rect.y = rect.top;
	window->rect.width = rect.right - rect.left;
	window->rect.height = rect.bottom - rect.top;
}
