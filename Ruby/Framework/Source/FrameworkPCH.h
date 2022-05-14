#pragma once

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include <map>
#include <map>
#include <memory.h>
#include <queue>
#include <string>
#include <vector>

#include "cJSON/cJSON.h"
#include "glad/glad.h"

#include "GL/GLHelpers.h"
#include "Math/Color.h"
#include "Math/MathHelpers.h"
#include "Math/Matrix4Float.h"
#include "Math/Vector.h"
#include "Utility/DebugUtility.h"
#include "Utility/FileUtility.h"
#include "Utility/ShaderProgram.h"
#include "Win32/FrameworkMain.h"

typedef Vector2Int ivec2;
typedef Vector3Int ivec3;
typedef Vector4Int ivec4;

#include "Events/CollisionEvent.h"
#include "Events/DoorEvent.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "GameCore/GameCore.h"
