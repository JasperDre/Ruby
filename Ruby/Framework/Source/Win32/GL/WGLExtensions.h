#pragma once

#include "wglext.h"

void WGL_InitExtensions();

extern PFNWGLSWAPINTERVALEXTPROC        wglSwapInterval;
extern PFNWGLGETSWAPINTERVALEXTPROC     wglGetSwapInterval;