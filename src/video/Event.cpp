#include <vix\vxEvent.h>
#include <Windows.h>


VIX_CODE_BEGIN



void defaultEventFunc(vxEvent* e) { printf("default event handler - %s\n", vxEvent_name(e->type)); }
vxEventFunc eventFunc = defaultEventFunc;


VIX_API
bool vxEvent_next()
{
	MSG msg;
	bool res = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0;
	return res && DispatchMessage(&msg);
}

VIX_API
void vxEvent_func(vxEventFunc func)
{
	eventFunc = func ? func : defaultEventFunc;
}

VIX_API
const char* vxEvent_name(vxEventType type)
{
#define CASE(type) case type: return #type;

	switch (type) {
		CASE(vxEvent_Unknown);
		CASE(vxEvent_Quit);
		CASE(vxEvent_WindowClose);
		CASE(vxEvent_WindowMove);
		CASE(vxEvent_WindowResize);
		CASE(vxEvent_WindowBeginResizeMove);
		CASE(vxEvent_WindowEndResizeMove);
		CASE(vxEvent_WindowRedraw);
		CASE(vxEvent_MouseMove);
		CASE(vxEvent_MouseDown);
		CASE(vxEvent_MouseUp);
		CASE(vxEvent_KeyDown);
		CASE(vxEvent_KeyUp);
		CASE(vxEvent_Count);
	default:
		return "None";
	}

#undef CASE
}



VIX_CODE_END

