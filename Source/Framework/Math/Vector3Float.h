#pragma once

#include "Vector2Float.h"

class Vector3Float
{
public:
    Vector3Float() : myX(0.0f), myY(0.0f), myZ(0.0f) {}
    Vector3Float(float aValue) : myX(aValue), myY(aValue), myZ(aValue) {}
    Vector3Float(float anX, float aY) : myX(anX), myY(aY), myZ(0.0f) {}
    Vector3Float(float anX, float aY, float aZ) : myX(anX), myY(aY), myZ(aZ) {}
    Vector3Float(Vector2Float v2) { myX = v2.myX; myY = v2.myY; myZ = 0; }
    Vector3Float(Vector2Float v2, float nz) { myX = v2.myX; myY = v2.myY; myZ = nz; }

    [[nodiscard]] Vector2Float XY() const { return Vector2Float(myX, myY); }

    void Set(float nx, float ny, float nz) { myX = nx; myY = ny; myZ = nz; }
    [[nodiscard]] float LengthSquared() const { return myX * myX + myY * myY + myZ * myZ; }
    [[nodiscard]] float Length() const;

    [[nodiscard]] Vector3Float GetNormalized() const;
    [[nodiscard]] Vector3Float Normalize();
    [[nodiscard]] Vector3Float Cross(const Vector3Float& o) const { return Vector3Float((myY * o.myZ - myZ * o.myY), (myZ * o.myX - myX * o.myZ), (myX * o.myY - myY * o.myX)); }
    [[nodiscard]] float Dot(const Vector3Float &o) const { return myX * o.myX + myY * o.myY + myZ * o.myZ; }
    [[nodiscard]] Vector3Float Add(const Vector3Float& o) const { return Vector3Float(myX + o.myX, myY + o.myY, myZ + o.myZ); }
    [[nodiscard]] Vector3Float Sub(const Vector3Float& o) const { return Vector3Float(myX - o.myX, myY - o.myY, myZ - o.myZ); }
    [[nodiscard]] Vector3Float Scale(const float o) const { return Vector3Float(myX * o, myY * o, myZ * o); }
    [[nodiscard]] Vector3Float MultiplyComponents(const Vector3Float& o) const { return Vector3Float(myX * o.myX, myY * o.myY, myZ * o.myZ); }
    [[nodiscard]] Vector3Float DivideComponents(const Vector3Float& o) const { return Vector3Float(myX / o.myX, myY / o.myY, myZ / o.myZ); }

    bool operator ==(const Vector3Float& o) const;
    bool operator !=(const Vector3Float& o) const;

    Vector3Float operator -() const { return Vector3Float(-myX, -myY, -myZ); }
    Vector3Float operator *(const float o) const { return Vector3Float(myX * o, myY * o, myZ * o); }
    Vector3Float operator /(const float o) const { return Vector3Float(myX / o, myY / o, myZ / o); }
    Vector3Float operator +(const float o) const { return Vector3Float(myX + o, myY + o, myZ + o); }
    Vector3Float operator -(const float o) const { return Vector3Float(myX - o, myY - o, myZ - o); }
    Vector3Float operator *(const Vector3Float& o) const { return Vector3Float(myX * o.myX, myY * o.myY, myZ * o.myZ); }
    Vector3Float operator /(const Vector3Float& o) const { return Vector3Float(myX / o.myX, myY / o.myY, myZ / o.myZ); }
    Vector3Float operator +(const Vector3Float& o) const { return Vector3Float(myX + o.myX, myY + o.myY, myZ + o.myZ); }
    Vector3Float operator -(const Vector3Float& o) const { return Vector3Float(myX - o.myX, myY - o.myY, myZ - o.myZ); }
    Vector3Float operator *=(const float o) { myX *= o; myY *= o; myZ *= o; return *this; }
    Vector3Float operator /=(const float o) { myX /= o; myY /= o; myZ /= o; return *this; }
    Vector3Float operator +=(const float o) { myX += o; myY += o; myZ += o; return *this; }
    Vector3Float operator -=(const float o) { myX -= o; myY -= o; myZ -= o; return *this; }
    Vector3Float operator *=(const Vector3Float& o) { myX *= o.myX; myY *= o.myY; myZ *= o.myZ; return *this; }
    Vector3Float operator /=(const Vector3Float& o) { myX /= o.myX; myY /= o.myY; myZ /= o.myZ; return *this; }
    Vector3Float operator +=(const Vector3Float& o) { myX += o.myX; myY += o.myY; myZ += o.myZ; return *this; }
    Vector3Float operator -=(const Vector3Float& o) { myX -= o.myX; myY -= o.myY; myZ -= o.myZ; return *this; }

    float& operator[](int i);

    float myX;
    float myY;
    float myZ;
};

inline Vector3Float operator *(float scalar, const Vector3Float& vector) { return Vector3Float(scalar * vector.myX, scalar * vector.myY, scalar * vector.myZ); }
inline Vector3Float operator /(float scalar, const Vector3Float& vector) { return Vector3Float(scalar / vector.myX, scalar / vector.myY, scalar / vector.myZ); }
inline Vector3Float operator +(float scalar, const Vector3Float& vector) { return Vector3Float(scalar + vector.myX, scalar + vector.myY, scalar + vector.myZ); }
inline Vector3Float operator -(float scalar, const Vector3Float& vector) { return Vector3Float(scalar - vector.myX, scalar - vector.myY, scalar - vector.myZ); }