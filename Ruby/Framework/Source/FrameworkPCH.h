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
#include <string>
#include <map>

#include "cJSON/cJSON.h"
#include "glad/glad.h"

#if WIN32
#include "Win32/Utility/WindowsUtility.h"
#endif
#include "GL/GLHelpers.h"
#include "Math/Color.h"
#include "Math/MathHelpers.h"
#include "Math/Matrix4Float.h"
#include "Math/Vector.h"
#include "Utility/FileUtility.h"
#include "Utility/ShaderProgram.h"

typedef Vector2Int ivec2;
typedef Vector3Int ivec3;
typedef Vector4Int ivec4;

#include "Events/CollisionEvent.h"
#include "Events/DoorEvent.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "GameCore/GameCore.h"

#if WIN32
#include "Win32/FrameworkMain.h"
#endif
