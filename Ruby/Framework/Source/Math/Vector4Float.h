#pragma once

#include "Vector3Float.h"

class Vector4Float
{
public:
	Vector4Float() : myX(0.0f), myY(0.0f), myZ(0.0f), myW(0.0f) {}
	Vector4Float(float nx, float ny, float nz, float nw) { myX = nx; myY = ny; myZ = nz; myW = nw; }
	Vector4Float(Vector2Float vec, float nz, float nw) { myX = vec.myX; myY = vec.myY; myZ = nz; myW = nw; }
	Vector4Float(Vector3Float vec, float nw) { myX = vec.myX; myY = vec.myY; myZ = vec.myZ; myW = nw; }

	[[nodiscard]] Vector3Float XYZ() const { return Vector3Float(myX, myY, myZ); }

	void Set(float nx, float ny, float nz, float nw) { myX = nx; myY = ny; myZ = nz; myW = nw; }
	[[nodiscard]] float LengthSquared() const { return myX * myX + myY * myY + myZ * myZ + myW * myW; }
	[[nodiscard]] float Length() const;

	[[nodiscard]] Vector4Float GetNormalized() const;
	Vector4Float Normalize();

	Vector4Float operator -() const { return Vector4Float(-myX, -myY, -myZ, -myW); }
	Vector4Float operator *(const float o) const { return Vector4Float(myX * o, myY * o, myZ * o, myW * o); }
	Vector4Float operator /(const float o) const { return Vector4Float(myX / o, myY / o, myZ / o, myW / o); }
	Vector4Float operator +(const float o) const { return Vector4Float(myX + o, myY + o, myZ + o, myW + o); }
	Vector4Float operator -(const float o) const { return Vector4Float(myX - o, myY - o, myZ - o, myW - o); }
	Vector4Float operator *(const Vector4Float& o) const { return Vector4Float(myX * o.myX, myY * o.myY, myZ * o.myZ, myW * o.myW); }
	Vector4Float operator /(const Vector4Float& o) const { return Vector4Float(myX / o.myX, myY / o.myY, myZ / o.myZ, myW / o.myW); }
	Vector4Float operator +(const Vector4Float& o) const { return Vector4Float(myX + o.myX, myY + o.myY, myZ + o.myZ, myW + o.myW); }
	Vector4Float operator -(const Vector4Float& o) const { return Vector4Float(myX - o.myX, myY - o.myY, myZ - o.myZ, myW - o.myW); }

	float& operator[] (int i);

	float myX;
	float myY;
	float myZ;
	float myW;
};

inline Vector4Float operator *(float scalar, const Vector4Float& vector) { return Vector4Float(scalar * vector.myX, scalar * vector.myY, scalar * vector.myZ, scalar * vector.myW); }
inline Vector4Float operator /(float scalar, const Vector4Float& vector) { return Vector4Float(scalar / vector.myX, scalar / vector.myY, scalar / vector.myZ, scalar / vector.myW); }
inline Vector4Float operator +(float scalar, const Vector4Float& vector) { return Vector4Float(scalar + vector.myX, scalar + vector.myY, scalar + vector.myZ, scalar + vector.myW); }
inline Vector4Float operator -(float scalar, const Vector4Float& vector) { return Vector4Float(scalar - vector.myX, scalar - vector.myY, scalar - vector.myZ, scalar - vector.myW); }