#pragma once

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#endif

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include <map>
#include <memory.h>
#include <queue>
#include <vector>

#if WIN32
#include <gl/GL.h>

#include "Win32/GL/glext.h"
#include "Win32/GL/wglext.h"
#endif

#include "cJSON/cJSON.h"

#if WIN32
#include "Win32/Utility/WindowsUtility.h"
#endif
#include "GL/GLHelpers.h"
#include "Math/MathHelpers.h"
#include "Math/Matrix4Float.h"
#include "Math/Vector.h"
#include "Utility/FileUtility.h"
#include "Utility/Helpers.h"
#include "Utility/ShaderProgram.h"

#if WIN32
#include "Win32/GL/GLExtensions.h"
#include "Win32/GL/WGLExtensions.h"
#endif

typedef Vector2Int ivec2;
typedef Vector3Int ivec3;
typedef Vector4Int ivec4;

#include "Events/CollisionEvent.h"
#include "Events/DoorEvent.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "Events/InputEvent.h"
#include "GameCore/GameCore.h"

#if WIN32
#include "Win32/FrameworkMain.h"
#endif
