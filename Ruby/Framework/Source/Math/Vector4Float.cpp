#include "FrameworkPCH.h"
#include "Vector4Float.h"

float Vector4Float::Length() const
{
	return sqrtf(myX * myX + myY * myY + myZ * myZ + myW * myW);
}

Vector4Float Vector4Float::GetNormalized() const
{
	float length = Length();
	if (IsEqualFloat(length, 0.0f))
		return Vector4Float(myX, myY, myZ, myW);

	length = 1.0f / length;

	return Vector4Float(myX * length, myY * length, myZ * length, myW * length);
}

Vector4Float Vector4Float::Normalize()
{
	const float length = Length();
	if (!IsEqualFloat(length, 0.0f))
	{
		myX /= length;
		myY /= length;
		myZ /= length;
		myW /= length;
	}

	return *this;
}

float& Vector4Float::operator[](int i)
{
	assert(i >= 0 && i < 4);
	return *(&myX + i);
}
