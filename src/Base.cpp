#pragma comment(lib, "opengl32.lib")

#include <vix\internal\Base.h>
#include <Windows.h>
#include <string.h>


VIX_CODE_BEGIN


VIX_API
float vxRandom_factor()
{
	float number = cast(float, rand() % 1001);
	return number / 1000;
}

VIX_API
float vxRandom_range(float min, float max)
{
	float number = (max - min) * vxRandom_factor();
	return number + min;
}

VIX_API
void vxDebug_error(const char* msg)
{
	MessageBox(NULL, msg, "Fatal Error", MB_OK | MB_ICONEXCLAMATION);
	exit(0);
}

VIX_API
bool vxDebug_log(const char* msg)
{
	return MessageBox(NULL, msg, "Log", MB_OKCANCEL | MB_HELP) == IDOK;
}

VIX_API
void vxTimer_sleep(uint32_t milliseconds)
{
	Sleep(milliseconds);
}


VIX_CODE_END
