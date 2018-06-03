#pragma once
#include "vxBase.h"

VIX_CODE_BEGIN

#define vxOpenGL_isBond(glcontext) cast(bool, *cast(bool*, glcontext))

VIX_API vxGLContext* vxOpenGL_createContext(vxWindow* window);
VIX_API void vxOpenGL_deleteContext(vxGLContext* glcontext);

VIX_API void vxOpenGL_bindContext(vxGLContext* glcontext, vxWindow* window);
VIX_API void vxOpenGL_unbindContext(vxGLContext* glcontext);


VIX_CODE_END