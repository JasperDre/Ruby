#pragma once

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
    [[nodiscard]] float LengthSquared() const { return static_cast<float>(x * x + y * y + z * z + w * w); }
    [[nodiscard]] float Length() const;

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
