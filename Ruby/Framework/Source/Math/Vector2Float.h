#pragma once

class Vector2Float
{
public:
    Vector2Float() : myX(0.0f), myY(0.0f) {}
    Vector2Float(float aValue) : myX(aValue), myY(aValue) {}
    Vector2Float(float anX, float aY) { myX = anX; myY = aY; }

    void Set(float anX, float aY) { myX = anX; myY = aY; }
    [[nodiscard]] float LengthSquared() const { return myX * myX + myY * myY; }
    [[nodiscard]] float Length() const;

    [[nodiscard]] Vector2Float GetNormalized() const;
    [[nodiscard]] Vector2Float Normalize();
    [[nodiscard]] float Dot(const Vector2Float& o) const { return myX * o.myX + myY * o.myY; }
    [[nodiscard]] Vector2Float Add(const Vector2Float& o) const { return Vector2Float(myX + o.myX, myY + o.myY); }
    [[nodiscard]] Vector2Float Sub(const Vector2Float& o) const { return Vector2Float(myX - o.myX, myY - o.myY); }
    [[nodiscard]] Vector2Float Scale(const float o) const { return Vector2Float(myX * o, myY * o); }

    bool operator ==(const Vector2Float& o) const;
    bool operator !=(const Vector2Float& o) const;

    Vector2Float operator -() const { return Vector2Float(-myX, -myY); }
    Vector2Float operator *(const float o) const { return Vector2Float(myX * o, myY * o); }
    Vector2Float operator /(const float o) const { return Vector2Float(myX / o, myY / o); }
    Vector2Float operator +(const float o) const { return Vector2Float(myX + o, myY + o); }
    Vector2Float operator -(const float o) const { return Vector2Float(myX - o, myY - o); }
    Vector2Float operator *(const Vector2Float& o) const { return Vector2Float(myX * o.myX, myY * o.myY); }
    Vector2Float operator /(const Vector2Float& o) const { return Vector2Float(myX / o.myX, myY / o.myY); }
    Vector2Float operator +(const Vector2Float& o) const { return Vector2Float(myX + o.myX, myY + o.myY); }
    Vector2Float operator -(const Vector2Float& o) const { return Vector2Float(myX - o.myX, myY - o.myY); }
    Vector2Float operator *=(const float o) { myX *= o; myY *= o; return *this; }
    Vector2Float operator /=(const float o) { myX /= o; myY /= o; return *this; }
    Vector2Float operator +=(const float o) { myX += o; myY += o; return *this; }
    Vector2Float operator -=(const float o) { myX -= o; myY -= o; return *this; }
    Vector2Float operator *=(const Vector2Float& o) { myX *= o.myX; myY *= o.myY; return *this; }
    Vector2Float operator /=(const Vector2Float& o) { myX /= o.myX; myY /= o.myY; return *this; }
    Vector2Float operator +=(const Vector2Float& o) { myX += o.myX; myY += o.myY; return *this; }
    Vector2Float operator -=(const Vector2Float& o) { myX -= o.myX; myY -= o.myY; return *this; }

    float& operator[](int i);

    float myX;
    float myY;
};

inline Vector2Float operator *(float scalar, const Vector2Float& vector) { return Vector2Float(scalar * vector.myX, scalar * vector.myY); }
inline Vector2Float operator /(float scalar, const Vector2Float& vector) { return Vector2Float(scalar / vector.myX, scalar / vector.myY); }
inline Vector2Float operator +(float scalar, const Vector2Float& vector) { return Vector2Float(scalar + vector.myX, scalar + vector.myY); }
inline Vector2Float operator -(float scalar, const Vector2Float& vector) { return Vector2Float(scalar - vector.myX, scalar - vector.myY); }