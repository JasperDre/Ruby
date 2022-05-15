#include "FrameworkPCH.h"
#include "Vector3Int.h"

float Vector3Int::Length() const
{
	return std::sqrtf(static_cast<float>(x * x + y * y + z * z));
}
