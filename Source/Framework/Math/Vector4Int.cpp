#include "FrameworkPCH.h"
#include "Vector4Int.h"

float Vector4Int::Length() const
{
	return std::sqrtf(static_cast<float>(x * x + y * y + z * z + w * w));
}
