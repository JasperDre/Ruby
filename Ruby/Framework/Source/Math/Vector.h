#pragma once

#include "Vector2Float.h"

class Vector3
{
public:
    float x;
    float y;
    float z;

public:
    Vector3() {}
    Vector3(float nxyz) { x = nxyz; y = nxyz; z = nxyz; }
    Vector3(float nx, float ny) { x = nx; y = ny; z = 0; }
    Vector3(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }
    Vector3(Vector2Float v2) { x = v2.myX; y = v2.myY; z = 0; }
    Vector3(Vector2Float v2, float nz) { x = v2.myX; y = v2.myY; z = nz; }

    inline Vector2Float XY() { return Vector2Float( x, y ); }

    inline void Set(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }
    inline float LengthSquared() const { return x*x + y*y + z*z; }
    inline float Length() const { return sqrtf(x*x + y*y + z*z); }

    inline Vector3 GetNormalized() const { float len = Length(); if( IsEqualFloat(len,0) ) return Vector3(x,y,z); len = 1.0f/len; return Vector3(x*len, y*len, z*len);}
    inline Vector3 Normalize() { float len = Length(); if( !IsEqualFloat(len,0) ) { x /= len; y /= len; z /= len; } return *this; }
    inline Vector3 Cross(const Vector3& o) const { return Vector3( (y*o.z - z*o.y), (z*o.x - x*o.z), (x*o.y - y*o.x) ); }
    inline float Dot(const Vector3 &o) const { return x*o.x + y*o.y + z*o.z; }
    inline Vector3 Add(const Vector3& o) const { return Vector3(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline Vector3 Sub(const Vector3& o) const { return Vector3(this->x - o.x, this->y - o.y, this->z - o.z); }
    inline Vector3 Scale(const float o) const { return Vector3(this->x * o, this->y * o, this->z * o); }
    inline Vector3 MultiplyComponents(const Vector3& o) const { return Vector3(this->x * o.x, this->y * o.y, this->z * o.z); }
    inline Vector3 DivideComponents(const Vector3& o) const { return Vector3(this->x / o.x, this->y / o.y, this->z / o.z); }
    //inline Vector3 MultiplyComponents(const Vector3Int& o) const { return Vector3(this->myX * o.myX, this->y * o.y, this->z * o.z); }

    inline bool operator ==(const Vector3& o) const { return IsEqualFloat(this->x, o.x) && IsEqualFloat(this->y, o.y) && IsEqualFloat(this->z, o.z); }
    inline bool operator !=(const Vector3& o) const { return !IsEqualFloat(this->x, o.x) || !IsEqualFloat(this->y, o.y) || !IsEqualFloat(this->z, o.z); }

    inline Vector3 operator -() const { return Vector3(-this->x, -this->y, -this->z); }
    inline Vector3 operator *(const float o) const { return Vector3(this->x * o, this->y * o, this->z * o); }
    inline Vector3 operator /(const float o) const { return Vector3(this->x / o, this->y / o, this->z / o); }
    inline Vector3 operator +(const float o) const { return Vector3(this->x + o, this->y + o, this->z + o); }
    inline Vector3 operator -(const float o) const { return Vector3(this->x - o, this->y - o, this->z - o); }
    inline Vector3 operator *(const Vector3& o) const { return Vector3(this->x * o.x, this->y * o.y, this->z * o.z); }
    inline Vector3 operator /(const Vector3& o) const { return Vector3(this->x / o.x, this->y / o.y, this->z / o.z); }
    inline Vector3 operator +(const Vector3& o) const { return Vector3(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline Vector3 operator -(const Vector3& o) const { return Vector3(this->x - o.x, this->y - o.y, this->z - o.z); }

    inline Vector3 operator *=(const float o) { this->x *= o; this->y *= o; this->z *= o; return *this; }
    inline Vector3 operator /=(const float o) { this->x /= o; this->y /= o; this->z /= o; return *this; }
    inline Vector3 operator +=(const float o) { this->x += o; this->y += o; this->z += o; return *this; }
    inline Vector3 operator -=(const float o) { this->x -= o; this->y -= o; this->z -= o; return *this; }
    inline Vector3 operator *=(const Vector3& o) { this->x *= o.x; this->y *= o.y; this->z *= o.z; return *this; }
    inline Vector3 operator /=(const Vector3& o) { this->x /= o.x; this->y /= o.y; this->z /= o.z; return *this; }
    inline Vector3 operator +=(const Vector3& o) { this->x += o.x; this->y += o.y; this->z += o.z; return *this; }
    inline Vector3 operator -=(const Vector3& o) { this->x -= o.x; this->y -= o.y; this->z -= o.z; return *this; }

    float& operator[] (int i) { assert(i>=0 && i<3); return *(&x + i); }

    //inline void operator =(const Vector2Float& o) { myX = o.myX; y = o.y; z = 0; } // couldn't make this work, used a constructor instead.
};

inline Vector3 operator *(float scalar, const Vector3& vector) { return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3 operator /(float scalar, const Vector3& vector) { return Vector3(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3 operator +(float scalar, const Vector3& vector) { return Vector3(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3 operator -(float scalar, const Vector3& vector) { return Vector3(scalar - vector.x, scalar - vector.y, scalar - vector.z); }

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4() {}
    Vector4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }
    Vector4(Vector2Float vec, float nz, float nw) { x = vec.myX; y = vec.myY; z = nz; w = nw; }
    Vector4(Vector3 vec, float nw) { x = vec.x; y = vec.y; z = vec.z; w = nw; }
    //virtual ~Vector4() {}

    inline Vector3 XYZ() { return Vector3( x, y, z ); }

    inline void Set(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }
    inline float LengthSquared() const {return x*x + y*y + z*z + w*w;}
    inline float Length() const { return sqrtf(x*x + y*y + z*z + w*w); }

    inline Vector4 GetNormalized() const { float len = Length(); if( IsEqualFloat(len,0) ) return Vector4(x,y,z,w); len = 1.0f/len; return Vector4(x*len, y*len, z*len, w*len); }
    inline Vector4 Normalize() { float len = Length(); if( !IsEqualFloat(len,0) ) { x /= len; y /= len; z /= len; w /= len; } return *this; }
    //Vector4 CrossProduct(const Vector4& b, const Vector4& c)
    // from http://www.gamedev.net/topic/269241-4d-vector-class/
    //  not sure if right and have no use for it.
    //{
    //    //Precompute some 2x2 matrix determinants for speed
    //    float Pxy = b.myX*c.y - c.myX*b.y;
    //    float Pxz = b.myX*c.z - c.myX*b.z;
    //    float Pxw = b.myX*c.w - c.myX*b.w;
    //    float Pyz = b.y*c.z - c.y*b.z;
    //    float Pyw = b.y*c.w - c.y*b.w;
    //    float Pzw = b.z*c.w - c.z*b.w;
    //    return Vector4(
    //        y*Pzw - z*Pyw + w*Pyz,    //Note the lack of 'myX' in this line
    //        z*Pxw - myX*Pzw - w*Pxz,    //y, Etc.
    //        myX*Pyw - y*Pxw + w*Pxy,
    //        y*Pxz - myX*Pyz - z*Pxy
    //        );
    //}

    inline Vector4 operator -() const { return Vector4(-this->x, -this->y, -this->z, -this->w); }
    inline Vector4 operator *(const float o) const { return Vector4(this->x * o, this->y * o, this->z * o, this->w * o); }
    inline Vector4 operator /(const float o) const { return Vector4(this->x / o, this->y / o, this->z / o, this->w / o); }
    inline Vector4 operator +(const float o) const { return Vector4(this->x + o, this->y + o, this->z + o, this->w + o); }
    inline Vector4 operator -(const float o) const { return Vector4(this->x - o, this->y - o, this->z - o, this->w - o); }
    inline Vector4 operator *(const Vector4& o) const { return Vector4(this->x * o.x, this->y * o.y, this->z * o.z, this->w * o.w); }
    inline Vector4 operator /(const Vector4& o) const { return Vector4(this->x / o.x, this->y / o.y, this->z / o.z, this->w / o.w); }
    inline Vector4 operator +(const Vector4& o) const { return Vector4(this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w); }
    inline Vector4 operator -(const Vector4& o) const { return Vector4(this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w); }

    float& operator[] (int i) { assert(i>=0 && i<4); return *(&x + i); }
};

inline Vector4 operator *(float scalar, const Vector4& vector) { return Vector4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w); }
inline Vector4 operator /(float scalar, const Vector4& vector) { return Vector4(scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w); }
inline Vector4 operator +(float scalar, const Vector4& vector) { return Vector4(scalar + vector.x, scalar + vector.y, scalar + vector.z, scalar + vector.w); }
inline Vector4 operator -(float scalar, const Vector4& vector) { return Vector4(scalar - vector.x, scalar - vector.y, scalar - vector.z, scalar - vector.w); }

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

    inline Vector3 MultiplyComponents(const Vector3& o) const { return Vector3(this->x * o.x, this->y * o.y, this->z * o.z); }
    inline Vector3Int MultiplyComponents(const Vector3Int& o) const { return Vector3Int(this->x * o.x, this->y * o.y, this->z * o.z); }

    inline bool operator ==(const Vector3Int& o) const { return this->x == o.x && this->y == o.y && this->z == o.z; }
    inline bool operator !=(const Vector3Int& o) const { return this->x != o.x || this->y != o.y || this->z != o.z; }

    inline Vector3Int operator -() const { return Vector3Int(-this->x, -this->y, -this->z); }
    inline Vector3 operator *(const float o) const { return Vector3(this->x * o, this->y * o, this->z * o); }
    inline Vector3 operator /(const float o) const { return Vector3(this->x / o, this->y / o, this->z / o); }
    inline Vector3 operator +(const float o) const { return Vector3(this->x + o, this->y + o, this->z + o); }
    inline Vector3 operator -(const float o) const { return Vector3(this->x - o, this->y - o, this->z - o); }
    inline Vector3Int operator *(const int o) const { return Vector3Int(this->x * o, this->y * o, this->z * o); }
    inline Vector3Int operator /(const int o) const { return Vector3Int(this->x / o, this->y / o, this->z / o); }
    inline Vector3Int operator +(const int o) const { return Vector3Int(this->x + o, this->y + o, this->z + o); }
    inline Vector3Int operator -(const int o) const { return Vector3Int(this->x - o, this->y - o, this->z - o); }
    inline Vector3 operator *(const Vector3& o) const { return Vector3(this->x * o.x, this->y * o.y, this->z * o.z); }
    inline Vector3 operator /(const Vector3& o) const { return Vector3(this->x / o.x, this->y / o.y, this->z / o.z); }
    inline Vector3 operator +(const Vector3& o) const { return Vector3(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline Vector3 operator -(const Vector3& o) const { return Vector3(this->x - o.x, this->y - o.y, this->z - o.z); }
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

inline Vector3 operator *(float scalar, const Vector3Int& vector) { return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3 operator /(float scalar, const Vector3Int& vector) { return Vector3(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3 operator +(float scalar, const Vector3Int& vector) { return Vector3(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3 operator -(float scalar, const Vector3Int& vector) { return Vector3(scalar - vector.x, scalar - vector.y, scalar - vector.z); }
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