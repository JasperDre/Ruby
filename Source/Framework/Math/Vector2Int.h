#pragma once

class Vector2Int
{
public:
    int x;
    int y;

    Vector2Int() : x(0), y(0) {}
    Vector2Int(int nx, int ny) { x = nx; y = ny; }

    void Set(int nx, int ny) { x = nx; y = ny; }
    [[nodiscard]] float LengthSquared() const { return static_cast<float>(x * x + y * y); }
    [[nodiscard]] float Length() const;

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
