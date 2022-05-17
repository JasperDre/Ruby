#include "Vector3Int.h"

#include <cassert>
#include <cmath>

float Vector3Int::Length() const
{
	return std::sqrtf(static_cast<float>(x * x + y * y + z * z));
}

int& Vector3Int::operator[](int i)
{
	assert(i>=0 && i<3); return *(&x + i);
}
