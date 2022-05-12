#include "FrameworkPCH.h"
#include "Vector2Float.h"

float Vector2Float::Length() const
{
	return sqrtf(myX * myX + myY * myY);
}

Vector2Float Vector2Float::GetNormalized() const
{
	float length = Length();
	if (IsEqualFloat(length, 0.0f))
		return Vector2Float(myX, myY);

	length = 1.0f / length;

	return Vector2Float(myX * length, myY * length);
}

Vector2Float Vector2Float::Normalize()
{
	const float length = Length();
	if (!IsEqualFloat(length, 0.0f))
	{
		myX /= length;
		myY /= length;
	}

	return *this;
}

bool Vector2Float::operator==(const Vector2Float& o) const
{
	return IsEqualFloat(myX, o.myX) && IsEqualFloat(myY, o.myY);
}

bool Vector2Float::operator!=(const Vector2Float& o) const
{
	return !IsEqualFloat(myX, o.myX) || !IsEqualFloat(myY, o.myY);
}

float& Vector2Float::operator[](int i)
{
	assert(i >= 0 && i < 2);
	return *(&myX + i);
}
