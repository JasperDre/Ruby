#include "FrameworkPCH.h"
#include "Vector4Float.h"

float Vector4Float::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vector4Float Vector4Float::GetNormalized() const
{
	float length = Length();
	if (IsEqualFloat(length, 0.0f))
		return Vector4Float(x, y, z, w);

	length = 1.0f / length;

	return Vector4Float(x * length, y * length, z * length, w * length);
}

Vector4Float Vector4Float::Normalize()
{
	const float length = Length();
	if (!IsEqualFloat(length, 0.0f))
	{
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	return *this;
}

float& Vector4Float::operator[](int i)
{
	assert(i >= 0 && i < 4);
	return *(&x + i);
}
