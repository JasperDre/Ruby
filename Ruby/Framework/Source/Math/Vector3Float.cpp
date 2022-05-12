#include "FrameworkPCH.h"
#include "Vector3Float.h"

float Vector3Float::Length() const
{
	return sqrtf(myX * myX + myY * myY + myZ * myZ);
}

Vector3Float Vector3Float::GetNormalized() const
{
	float length = Length();
	if (IsEqualFloat(length, 0.0f))
		return Vector3Float(myX, myY, myZ);
	
	length = 1.0f / length;
	
	return Vector3Float(myX * length, myY * length, myZ * length);
}

Vector3Float Vector3Float::Normalize()
{
	const float length = Length();
	if (!IsEqualFloat(length,0) )
	{ 
		myX /= length; myY /= length;
		myZ /= length;
	}
	
	return *this;
}

float& Vector3Float::operator[](int i)
{
	assert(i >= 0 && i < 3);
	return *(&myX + i);
}
