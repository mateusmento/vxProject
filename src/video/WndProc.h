#pragma once
#include <Windows.h>
#include <Windowsx.h>


#include "MessageHandlers.h"



VIX_CODE_BEGIN

extern vxEventFunc eventFunc;


// TODO1: handle more messages
// TODO2: allow user define its own WndProc
HRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static uint32_t window_count = 0;

	vxEvent event;
	vxEventType type = vxEvent_Unknown;
	vxWindow* window = (vxWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	LRESULT res = 0;
	vxKey key = vxKey_None;
	vxMouse button = vxMouse_None;
	int wheel = 0;

	HWND hWndEdit = NULL;

	switch (msg)
	{
	case WM_NCCREATE:
		window_count++;
		createHandler(hwnd, (CREATESTRUCT*)lparam);
		return DefWindowProc(hwnd, msg, wparam, lparam);

	case WM_SETFOCUS:
		SetFocus(hwnd);
		return 0;

	case WM_NCDESTROY:
		if (--window_count == 0) {
			type = vxEvent_Quit;
			goto HandleEvent;
		}
		return 0;

//// Windiow Event //////////////////////////////////////////////////////////////////////

	case WM_CLOSE:
		type = vxEvent_WindowClose;
		goto HandleEvent;

	case WM_MOVING:
		type = vxEvent_WindowMove;
		moveHandler(window, lparam);
		goto HandleEvent;

	case WM_SIZING:
		type = vxEvent_WindowResize;
		resizeHandler(window);
		goto HandleEvent;

	case WM_ENTERSIZEMOVE:
		type = vxEvent_WindowBeginResizeMove;
		goto HandleEvent;

	case WM_EXITSIZEMOVE:
		type = vxEvent_WindowEndResizeMove;
		goto HandleEvent;

	case WM_PAINT:
		type = vxEvent_WindowRedraw;
		ValidateRect(hwnd, NULL);
		goto HandleEvent;

//// Keyboard Event /////////////////////////////////////////////////////////////////////

	case WM_KEYDOWN:
		type = vxEvent_KeyDown;
		goto KeyEvent;

	case WM_KEYUP:
		type = vxEvent_KeyUp;
		goto KeyEvent;

//// Mouse Event ////////////////////////////////////////////////////////////////////////

	case WM_LBUTTONDOWN:
		button = vxMouse_Left;
		goto MouseDown;

	case WM_MBUTTONDOWN:
		button = vxMouse_Middle;
		goto MouseDown;

	case WM_RBUTTONDOWN:
		button = vxMouse_Right;
		goto MouseDown;

	case WM_XBUTTONDOWN:
		button = cast(vxMouse, vxMouse_Right + HIWORD(wparam));
		goto MouseDown;

	case WM_LBUTTONUP:
		button = vxMouse_Right;
		goto MouseUp;

	case WM_MBUTTONUP:
		button = vxMouse_Middle;
		goto MouseUp;

	case WM_RBUTTONUP:
		button = vxMouse_Right;
		goto MouseUp;

	case WM_XBUTTONUP:
		button = cast(vxMouse, vxMouse_Right + HIWORD(wparam));
		goto MouseUp;

	case WM_MOUSEMOVE:
		if (wparam == MK_LBUTTON) {
			button = vxMouse_Left;
		} else if (wparam == MK_RBUTTON) {
			button = vxMouse_Right;
		} else if (wparam == MK_MBUTTON) {
			button = vxMouse_Right;
		} else if (wparam == MK_XBUTTON1) {
			button = vxMouse_X1;
		} else if (wparam == MK_XBUTTON2) {
			button = vxMouse_X2;
		}
		type = vxEvent_MouseMove;
		goto MouseEvent;

	case WM_MOUSEHWHEEL:
		type = vxEvent_MouseWheel;
		wheel = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
		printf("Horizontal Wheel %i\n", wheel);
		break;

	case WM_MOUSEWHEEL:
		wheel = GET_WHEEL_DELTA_WPARAM(wparam);
		printf("Vertical Wheel %i\n", wheel);
		break;

	case WM_MOUSELEAVE:
		type = vxEvent_MouseLeave;
		break;


	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

KeyEvent:
	event.keyboard.key = (vxKey)wparam;
	goto HandleEvent;

MouseDown:
	type = vxEvent_MouseDown;
	goto MouseEvent;

MouseUp:
	type = vxEvent_MouseUp;
	goto MouseEvent;

MouseEvent:
	event.mouse.button = button;
	event.mouse.wheel = wheel;
	event.mouse.position.x = GET_X_LPARAM(lparam);
	event.mouse.position.y = GET_Y_LPARAM(lparam);


HandleEvent:
	event.type = type;
	event.window.window = window;
	eventFunc(&event);
	return res;
}

VIX_CODE_END
