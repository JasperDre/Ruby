#pragma once

#include "Vector3Float.h"

class Vector3Int
{
public:
    int x;
    int y;
    int z;

    Vector3Int() : x(0), y(0), z(0) {}
    Vector3Int(int nx, int ny, int nz) { x = nx; y = ny; z = nz; }

    void Set(int nx, int ny, int nz) { x = nx; y = ny; z = nz; }
    void Set(Vector3Int vec) { x = vec.x; y = vec.y; z = vec.z; }
    [[nodiscard]] int LengthSquared() const { return x*x + y*y + z*z; }
    [[nodiscard]] float Length() const;

    [[nodiscard]] Vector3Float MultiplyComponents(const Vector3Float& o) const { return Vector3Float(x * o.myX, y * o.myY, z * o.myZ); }
    [[nodiscard]] Vector3Int MultiplyComponents(const Vector3Int& o) const { return Vector3Int(x * o.x, y * o.y, z * o.z); }

    bool operator ==(const Vector3Int& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator !=(const Vector3Int& o) const { return x != o.x || y != o.y || z != o.z; }

    Vector3Int operator -() const { return Vector3Int(-x, -y, -z); }
    Vector3Float operator *(const float o) const { return Vector3Float(x * o, y * o, z * o); }
    Vector3Float operator /(const float o) const { return Vector3Float(x / o, y / o, z / o); }
    Vector3Float operator +(const float o) const { return Vector3Float(x + o, y + o, z + o); }
    Vector3Float operator -(const float o) const { return Vector3Float(x - o, y - o, z - o); }
    Vector3Int operator *(const int o) const { return Vector3Int(x * o, y * o, z * o); }
    Vector3Int operator /(const int o) const { return Vector3Int(x / o, y / o, z / o); }
    Vector3Int operator +(const int o) const { return Vector3Int(x + o, y + o, z + o); }
    Vector3Int operator -(const int o) const { return Vector3Int(x - o, y - o, z - o); }
    Vector3Float operator *(const Vector3Float& o) const { return Vector3Float(x * o.myX, y * o.myY, z * o.myZ); }
    Vector3Float operator /(const Vector3Float& o) const { return Vector3Float(x / o.myX, y / o.myY, z / o.myZ); }
    Vector3Float operator +(const Vector3Float& o) const { return Vector3Float(x + o.myX, y + o.myY, z + o.myZ); }
    Vector3Float operator -(const Vector3Float& o) const { return Vector3Float(x - o.myX, y - o.myY, z - o.myZ); }
    Vector3Int operator *(const Vector3Int& o) const { return Vector3Int(x * o.x, y * o.y, z * o.z); }
    Vector3Int operator /(const Vector3Int& o) const { return Vector3Int(x / o.x, y / o.y, z / o.z); }
    Vector3Int operator +(const Vector3Int& o) const { return Vector3Int(x + o.x, y + o.y, z + o.z); }
    Vector3Int operator -(const Vector3Int& o) const { return Vector3Int(x - o.x, y - o.y, z - o.z); }

    Vector3Int operator +=(const Vector3Int& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vector3Int operator -=(const Vector3Int& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }

    int& operator[](int i);
};

inline Vector3Float operator *(float scalar, const Vector3Int& vector) { return Vector3Float(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3Float operator /(float scalar, const Vector3Int& vector) { return Vector3Float(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3Float operator +(float scalar, const Vector3Int& vector) { return Vector3Float(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3Float operator -(float scalar, const Vector3Int& vector) { return Vector3Float(scalar - vector.x, scalar - vector.y, scalar - vector.z); }
inline Vector3Int operator *(int scalar, const Vector3Int& vector) { return Vector3Int(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3Int operator /(int scalar, const Vector3Int& vector) { return Vector3Int(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3Int operator +(int scalar, const Vector3Int& vector) { return Vector3Int(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3Int operator -(int scalar, const Vector3Int& vector) { return Vector3Int(scalar - vector.x, scalar - vector.y, scalar - vector.z); }
