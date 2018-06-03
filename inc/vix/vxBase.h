#pragma once

//// API Specific /////////////////////////////////////////////////////////////////////

#define VIX_EXPORT_API
#define VIX_USE_ASSERTION

#ifdef __cplusplus
#	define VIX_CODE_BEGIN extern "C" {
#	define VIX_CODE_END }
#else
#	define VIX_CODE_BEGIN
#	define VIX_CODE_END
#endif

#ifdef VIX_EXPORT_API
#	define VIX_DECLSPEC __declspec(dllexport)
#else
#	define VIX_DECLSPEC __declspec(dllimport)
#endif

#define VIX_API VIX_DECLSPEC

//// Macros ///////////////////////////////////////////////////////////////////////////


#ifndef cast
#	if defined(__cplusplus)
#		define cast(type, value) ((type)(value))
#	else
#		define cast(type, value) ((type)(value))
#	endif
#endif

#define null 0


#ifndef verify
#	define verify(expr, msg) ( (!(expr)) && (vxDebug_error(msg), 1) )
#endif

//// API Functions ////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


VIX_CODE_BEGIN

//// API Types ////////////////////////////////////////////////////////////////////////

typedef struct vxPoint vxPoint;
typedef struct vxRect vxRect;
typedef struct vxColor vxColor;

typedef struct vxWindow vxWindow;
typedef struct vxIWindow vxIWindow;

typedef struct vxGLContext vxGLContext;

struct vxRect
{
	int32_t x, y, width, height;
};

struct vxPoint
{
	int32_t x, y;
};

struct vxColor
{
	uint8_t r, g, b;
};


VIX_API void vxTimer_sleep(uint32_t milliseconds);

VIX_API void vxDebug_error(const char* msg);
VIX_API bool vxDebug_log(const char* msg);

VIX_API float vxRandom_factor();
VIX_API float vxRandom_range(float min, float max);


VIX_CODE_END


///////////////////////////////////////////////////////////////////////////////////////
