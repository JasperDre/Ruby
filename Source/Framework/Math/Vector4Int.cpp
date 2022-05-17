#include "Vector4Int.h"

#include <cmath>

float Vector4Int::Length() const
{
	return std::sqrtf(static_cast<float>(x * x + y * y + z * z + w * w));
}
