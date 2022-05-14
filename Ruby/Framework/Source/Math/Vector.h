#pragma once

#include "Vector4Float.h"

class Vector2Int
{
public:
    int x;
    int y;

    Vector2Int() : x(0), y(0) {}
    Vector2Int(int nx, int ny) { x = nx; y = ny; }

    void Set(int nx, int ny) { x = nx; y = ny; }
    [[nodiscard]] float LengthSquared() const { return static_cast<float>(x)*x + y*y; }
    [[nodiscard]] float Length() const { return sqrtf(static_cast<float>(x)*x + y*y); }

    bool operator ==(const Vector2Int& o) const { return x == o.x && y == o.y; }
    bool operator !=(const Vector2Int& o) const { return x != o.x || y != o.y; }

    Vector2Int operator -() const { return Vector2Int(-x, -y); }
    Vector2Int operator +(const Vector2Int& o) const { return Vector2Int(x + o.x, y + o.y); }
    Vector2Int operator -(const Vector2Int& o) const { return Vector2Int(x - o.x, y - o.y); }
};

inline Vector2Int operator *(int scalar, const Vector2Int& vector) { return Vector2Int(scalar * vector.x, scalar * vector.y); }
inline Vector2Int operator /(int scalar, const Vector2Int& vector) { return Vector2Int(scalar / vector.x, scalar / vector.y); }
inline Vector2Int operator +(int scalar, const Vector2Int& vector) { return Vector2Int(scalar + vector.x, scalar + vector.y); }
inline Vector2Int operator -(int scalar, const Vector2Int& vector) { return Vector2Int(scalar - vector.x, scalar - vector.y); }

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
    [[nodiscard]] float Length() const { return sqrtf(static_cast<float>(x)*x + y*y + z*z); }

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

    int& operator[](int i) { assert(i>=0 && i<3); return *(&x + i); }
};

inline Vector3Float operator *(float scalar, const Vector3Int& vector) { return Vector3Float(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3Float operator /(float scalar, const Vector3Int& vector) { return Vector3Float(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3Float operator +(float scalar, const Vector3Int& vector) { return Vector3Float(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3Float operator -(float scalar, const Vector3Int& vector) { return Vector3Float(scalar - vector.x, scalar - vector.y, scalar - vector.z); }
inline Vector3Int operator *(int scalar, const Vector3Int& vector) { return Vector3Int(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3Int operator /(int scalar, const Vector3Int& vector) { return Vector3Int(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3Int operator +(int scalar, const Vector3Int& vector) { return Vector3Int(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3Int operator -(int scalar, const Vector3Int& vector) { return Vector3Int(scalar - vector.x, scalar - vector.y, scalar - vector.z); }

class Vector4Int
{
public:
    int x;
    int y;
    int z;
    int w;

    Vector4Int() : x(0), y(0), z(0), w(0) {}
    Vector4Int(int nx, int ny, int nz, int nw) { x = nx; y = ny; z = nz; w = nw; }

    void Set(int nx, int ny, int nz, int nw) { x = nx; y = ny; z = nz; w = nw; }
    [[nodiscard]] float LengthSquared() const { return static_cast<float>(x)*x + y*y + z*z + w*w; }
    [[nodiscard]] float Length() const { return sqrtf(static_cast<float>(x)*x + y*y + z*z + w*w); }

    bool operator ==(const Vector4Int& o) const { return x == o.x && y == o.y && z == o.z && w == o.w; }
    bool operator !=(const Vector4Int& o) const { return x != o.x || y != o.y || z != o.z || w != o.w; }

    Vector4Int operator -() const { return Vector4Int(-x, -y, -z, -w); }
    Vector4Int operator +(const Vector4Int& o) const { return Vector4Int(x + o.x, y + o.y, z + o.z, w + o.w); }
    Vector4Int operator -(const Vector4Int& o) const { return Vector4Int(x - o.x, y - o.y, z - o.z, w - o.w); }
};

inline Vector4Int operator *(int scalar, const Vector4Int& vector) { return Vector4Int(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w); }
inline Vector4Int operator /(int scalar, const Vector4Int& vector) { return Vector4Int(scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w); }
inline Vector4Int operator +(int scalar, const Vector4Int& vector) { return Vector4Int(scalar + vector.x, scalar + vector.y, scalar + vector.z, scalar + vector.w); }
inline Vector4Int operator -(int scalar, const Vector4Int& vector) { return Vector4Int(scalar - vector.x, scalar - vector.y, scalar - vector.z, scalar - vector.w); }

class Rectangle
{
public:
    int x;
    int y;
    int w;
    int h;

    Rectangle() : x(0), y(0), w(0), h(0) {}
    Rectangle(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }

    void Set(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }
};