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
#include <random>
#include <string>
#include <vector>

#include "glad/glad.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "Events/CollisionEvent.h"
#include "Events/DoorEvent.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "GameCore/GameCore.h"
#include "GL/GLHelpers.h"
#include "Math/Color.h"
#include "Math/Matrix4Float.h"
#include "Math/Vector2Int.h"
#include "Math/Vector3Int.h"
#include "Math/Vector4Int.h"
#include "Utility/DebugUtility.h"
#include "Utility/FileUtility.h"
#include "Utility/MathUtility.h"
#include "Utility/ShaderProgram.h"
#include "Win32/FrameworkMain.h"
