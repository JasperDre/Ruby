#include "Vector2Int.h"

#include <cmath>

float Vector2Int::Length() const
{
	return std::sqrtf(static_cast<float>(x * x + y * y));
}
