#include "FrameworkPCH.h"
#include "Vector2Int.h"

float Vector2Int::Length() const
{
	return std::sqrtf(static_cast<float>(x * x + y * y));
}
