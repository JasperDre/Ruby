#pragma once

#include "Vector3Float.h"

class Vector2Int
{
public:
    int x;
    int y;

public:
    Vector2Int() {}
    Vector2Int(int nx, int ny) { x = nx; y = ny; }
    //virtual ~Vector2Int() {}

    inline void Set(int nx, int ny) { x = nx; y = ny; }
    inline float LengthSquared() const {return (float)x*x + y*y;}
    inline float Length() const {return sqrtf((float)x*x + y*y);}

    //inline Vector2Int Normalize() const {float len = Length(); if( IsEqualFloat(len,0) ) return Vector2Int(myX,y); len = 1.0f/len; return Vector2Int(myX*len, y*len);}

    inline bool operator ==(const Vector2Int& o) const { return this->x == o.x && this->y == o.y; }
    inline bool operator !=(const Vector2Int& o) const { return this->x != o.x || this->y != o.y; }

    inline Vector2Int operator -() const { return Vector2Int(-this->x, -this->y); }
    inline Vector2Int operator +(const Vector2Int& o) const { return Vector2Int(this->x + o.x, this->y + o.y); }
    inline Vector2Int operator -(const Vector2Int& o) const { return Vector2Int(this->x - o.x, this->y - o.y); }
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

public:
    Vector3Int() {}
    Vector3Int(int nx, int ny, int nz) { x = nx; y = ny; z = nz; }
    //virtual ~Vector3Int() {}

    inline void Set(int nx, int ny, int nz) { x = nx; y = ny; z = nz; }
    inline void Set(Vector3Int vec) { x = vec.x; y = vec.y; z = vec.z; }
    inline int LengthSquared() const { return x*x + y*y + z*z; }
    inline float Length() const { return sqrtf((float)x*x + y*y + z*z); }

    //inline Vector3Int Normalize() const {float len = Length(); if( IsEqualFloat(len,0) ) return Vector3Int(myX,y,z); len = 1.0f/len; return Vector3Int(myX*len, y*len, z*len);}
    //inline Vector3Int Cross(const Vector3Int& o) const {return Vector3Int( (y*o.z - z*o.y), (z*o.myX - myX*o.z), (myX*o.y - y*o.myX) );}

    inline Vector3Float MultiplyComponents(const Vector3Float& o) const { return Vector3Float(this->x * o.myX, this->y * o.myY, this->z * o.myZ); }
    inline Vector3Int MultiplyComponents(const Vector3Int& o) const { return Vector3Int(this->x * o.x, this->y * o.y, this->z * o.z); }

    inline bool operator ==(const Vector3Int& o) const { return this->x == o.x && this->y == o.y && this->z == o.z; }
    inline bool operator !=(const Vector3Int& o) const { return this->x != o.x || this->y != o.y || this->z != o.z; }

    inline Vector3Int operator -() const { return Vector3Int(-this->x, -this->y, -this->z); }
    inline Vector3Float operator *(const float o) const { return Vector3Float(this->x * o, this->y * o, this->z * o); }
    inline Vector3Float operator /(const float o) const { return Vector3Float(this->x / o, this->y / o, this->z / o); }
    inline Vector3Float operator +(const float o) const { return Vector3Float(this->x + o, this->y + o, this->z + o); }
    inline Vector3Float operator -(const float o) const { return Vector3Float(this->x - o, this->y - o, this->z - o); }
    inline Vector3Int operator *(const int o) const { return Vector3Int(this->x * o, this->y * o, this->z * o); }
    inline Vector3Int operator /(const int o) const { return Vector3Int(this->x / o, this->y / o, this->z / o); }
    inline Vector3Int operator +(const int o) const { return Vector3Int(this->x + o, this->y + o, this->z + o); }
    inline Vector3Int operator -(const int o) const { return Vector3Int(this->x - o, this->y - o, this->z - o); }
    inline Vector3Float operator *(const Vector3Float& o) const { return Vector3Float(this->x * o.myX, this->y * o.myY, this->z * o.myZ); }
    inline Vector3Float operator /(const Vector3Float& o) const { return Vector3Float(this->x / o.myX, this->y / o.myY, this->z / o.myZ); }
    inline Vector3Float operator +(const Vector3Float& o) const { return Vector3Float(this->x + o.myX, this->y + o.myY, this->z + o.myZ); }
    inline Vector3Float operator -(const Vector3Float& o) const { return Vector3Float(this->x - o.myX, this->y - o.myY, this->z - o.myZ); }
    inline Vector3Int operator *(const Vector3Int& o) const { return Vector3Int(this->x * o.x, this->y * o.y, this->z * o.z); }
    inline Vector3Int operator /(const Vector3Int& o) const { return Vector3Int(this->x / o.x, this->y / o.y, this->z / o.z); }
    inline Vector3Int operator +(const Vector3Int& o) const { return Vector3Int(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline Vector3Int operator -(const Vector3Int& o) const { return Vector3Int(this->x - o.x, this->y - o.y, this->z - o.z); }

    //inline Vector3Int operator *=(const float o) { this->myX *= o; this->y *= o; this->z *= o; return *this; }
    //inline Vector3Int operator /=(const float o) { this->myX /= o; this->y /= o; this->z /= o; return *this; }
    //inline Vector3Int operator +=(const float o) { this->myX += o; this->y += o; this->z += o; return *this; }
    //inline Vector3Int operator -=(const float o) { this->myX -= o; this->y -= o; this->z -= o; return *this; }
    //inline Vector3Int operator +=(const Vector3& o) { this->myX += o.myX; this->y += o.y; this->z += o.z; return *this; }
    //inline Vector3Int operator -=(const Vector3& o) { this->myX -= o.myX; this->y -= o.y; this->z -= o.z; return *this; }
    inline Vector3Int operator +=(const Vector3Int& o) { this->x += o.x; this->y += o.y; this->z += o.z; return *this; }
    inline Vector3Int operator -=(const Vector3Int& o) { this->x -= o.x; this->y -= o.y; this->z -= o.z; return *this; }

    int& operator[] (int i) { assert(i>=0 && i<3); return *(&x + i); }
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

public:
    Vector4Int() {}
    Vector4Int(int nx, int ny, int nz, int nw) { x = nx; y = ny; z = nz; w = nw; }
    //virtual ~Vector4Int() {}

    inline void Set(int nx, int ny, int nz, int nw) { x = nx; y = ny; z = nz; w = nw; }
    inline float LengthSquared() const {return (float)x*x + y*y + z*z + w*w;}
    inline float Length() const {return sqrtf((float)x*x + y*y + z*z + w*w);}

    //inline Vector4Int Normalize() const {float len = Length(); if( IsEqualFloat(len,0) ) return Vector4Int(myX,y,z); len = 1.0f/len; return Vector4Int(myX*len, y*len, z*len);}
    //inline Vector4Int Cross(const Vector4Int& o) const {return Vector4Int( (y*o.z - z*o.y), (z*o.myX - myX*o.z), (myX*o.y - y*o.myX) );}

    inline bool operator ==(const Vector4Int& o) const { return this->x == o.x && this->y == o.y && this->z == o.z && this->w == o.w; }
    inline bool operator !=(const Vector4Int& o) const { return this->x != o.x || this->y != o.y || this->z != o.z || this->w != o.w; }

    inline Vector4Int operator -() const { return Vector4Int(-this->x, -this->y, -this->z, -this->w); }
    inline Vector4Int operator +(const Vector4Int& o) const { return Vector4Int(this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w); }
    inline Vector4Int operator -(const Vector4Int& o) const { return Vector4Int(this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w); }
};

inline Vector4Int operator *(int scalar, const Vector4Int& vector) { return Vector4Int(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w); }
inline Vector4Int operator /(int scalar, const Vector4Int& vector) { return Vector4Int(scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w); }
inline Vector4Int operator +(int scalar, const Vector4Int& vector) { return Vector4Int(scalar + vector.x, scalar + vector.y, scalar + vector.z, scalar + vector.w); }
inline Vector4Int operator -(int scalar, const Vector4Int& vector) { return Vector4Int(scalar - vector.x, scalar - vector.y, scalar - vector.z, scalar - vector.w); }

class MyRect
{
public:
    int x;
    int y;
    int w;
    int h;

public:
    MyRect() {}
    MyRect(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }

    void Set(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }
};

template <class MyType> class Vector2T
{
public:
    MyType x;
    MyType y;

public:
    Vector2T() {}
    Vector2T(MyType nx, MyType ny) { x = nx; y = ny; }
    //Vector2T(MyType nx, MyType ny) { myX = (float)nx; y = (float)ny; }
    //virtual ~Vector2Int() {}

    inline void Set(MyType nx, MyType ny) { x = nx; y = ny; }
    inline float LengthSquared() const {return (float)x*x + y*y;}
    inline float Length() const {return sqrtf((float)x*x + y*y);}

    inline Vector2T<MyType> GetNormalized() const { float len = Length(); if( IsEqualFloat(len,0) ) return Vector2T<MyType>(x,y); len = 1.0f/len; return Vector2T<MyType>(x*len, y*len); }
    //inline Vector2T<MyType> Normalize() const {float len = Length(); if( IsEqualFloat(len,0) ) return Vector2T<MyType>(myX,y); len = 1.0f/len; return Vector2T<MyType>(myX*len, y*len);}

    inline bool operator ==(const Vector2T<MyType>& o) const { return this->x == o.x && this->y == o.y; }
    inline bool operator !=(const Vector2T<MyType>& o) const { return this->x != o.x || this->y != o.y; }

    inline Vector2T<MyType> operator -() const { return Vector2T<MyType>(-this->x, -this->y); }

    inline Vector2T<MyType> operator *(const float o) const { return Vector2T<MyType>(this->x * o, this->y * o); }
    inline Vector2T<MyType> operator /(const float o) const { return Vector2T<MyType>(this->x / o, this->y / o); }
    inline Vector2T<MyType> operator +(const Vector2Float& o) const { return Vector2T<MyType>(this->x + o.myX, this->y + o.myY); }
    inline Vector2T<MyType> operator -(const Vector2Float& o) const { return Vector2T<MyType>(this->x - o.myX, this->y - o.myY); }

    inline Vector2T<MyType> operator *=(const float o) { this->x *= o; this->y *= o; return *this; }
    inline Vector2T<MyType> operator /=(const float o) { this->x /= o; this->y /= o; return *this; }
    inline Vector2T<MyType> operator +=(const Vector2T<MyType>& o) { this->x += o.x; this->y += o.y; return *this; }
    inline Vector2T<MyType> operator -=(const Vector2T<MyType>& o) { this->x -= o.x; this->y -= o.y; return *this; }
};