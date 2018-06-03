#pragma once
#include "vxWindow.h"

VIX_CODE_BEGIN

enum vxEventType
{
	vxEvent_Unknown,
	vxEvent_Quit,

	vxEvent_WindowClose,
	vxEvent_WindowMove,
	vxEvent_WindowResize,
	vxEvent_WindowBeginResizeMove,
	vxEvent_WindowEndResizeMove,
	vxEvent_WindowRedraw,

	vxEvent_KeyDown,
	vxEvent_KeyUp,

	vxEvent_MouseDown,
	vxEvent_MouseUp,
	vxEvent_MouseMove,
	vxEvent_MouseWheel,
	vxEvent_MouseLeave,

	vxEvent_Count
};

enum vxKey
{
	vxKey_None,
	vxKey_LeftAlt,
	vxKey_RightAlt,
	vxKey_LeftCtrl,
	vxKey_RightCtrl,
	vxKey_Space,
	vxKey_Count
};

enum vxMouse
{
	vxMouse_None,
	vxMouse_Left,
	vxMouse_Middle,
	vxMouse_Right,
	vxMouse_X1,
	vxMouse_X2,
	vxMouse_Count
};


union vxEvent
{
	vxEventType type;

	struct {
		vxEventType type;
		vxWindow* window;
	} window;

	struct {
		vxEventType type;
		vxWindow* window;
		vxKey key;
	} keyboard;

	struct {
		vxEventType type;
		vxWindow* window;
		vxMouse button;
		vxPoint position;
		int wheel;
	} mouse;
};

typedef union vxEvent vxEvent;
typedef enum vxEventType vxEventType;
typedef enum vxKey vxKey;
typedef enum vxMouse vxMouse;


typedef void(*vxEventFunc)(vxEvent*);

VIX_API bool vxEvent_next();
VIX_API void vxEvent_func(vxEventFunc func);
VIX_API const char* vxEvent_name(vxEventType type);


VIX_CODE_END

