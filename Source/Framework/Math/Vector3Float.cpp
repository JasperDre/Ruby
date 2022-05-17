#include "Vector3Float.h"

#include <cassert>
#include <cmath>

#include "Utility/MathUtility.h"

float Vector3Float::Length() const
{
	return std::sqrtf(myX * myX + myY * myY + myZ * myZ);
}

Vector3Float Vector3Float::GetNormalized() const
{
	float length = Length();
	if (MathUtility::IsEqualFloat(length, 0.0f))
		return Vector3Float(myX, myY, myZ);
	
	length = 1.0f / length;
	
	return Vector3Float(myX * length, myY * length, myZ * length);
}

Vector3Float Vector3Float::Normalize()
{
	const float length = Length();
	if (!MathUtility::IsEqualFloat(length,0.0f))
	{
		myX /= length; myY /= length;
		myZ /= length;
	}

	return *this;
}

bool Vector3Float::operator==(const Vector3Float& o) const
{
	return MathUtility::IsEqualFloat(myX, o.myX)
		&& MathUtility::IsEqualFloat(myY, o.myY)
		&& MathUtility::IsEqualFloat(myZ, o.myZ);
}

bool Vector3Float::operator!=(const Vector3Float& o) const
{
	return !MathUtility::IsEqualFloat(myX, o.myX)
		|| !MathUtility::IsEqualFloat(myY, o.myY)
		|| !MathUtility::IsEqualFloat(myZ, o.myZ);
}

float& Vector3Float::operator[](int i)
{
	assert(i >= 0 && i < 3);
	return *(&myX + i);
}
