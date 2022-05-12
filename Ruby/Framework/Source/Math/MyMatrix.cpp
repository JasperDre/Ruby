#include "FrameworkPCH.h"
#include "MyMatrix.h"

#include "MathHelpers.h"
#include "Vector.h"

void MyMatrix::SetIdentity()
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0f;
    m11 = m22 = m33 = m44 = 1.0f;
}

void MyMatrix::SetAxesView(const Vector3Float& right, const Vector3Float& up, const Vector3Float& at, const Vector3Float& pos)
{
    m11 = right.myX; m21 = right.myY; m31 = right.myZ; m41 = pos.myX;
    m12 = up.myX; m22 = up.myY; m32 = up.myZ; m42 = pos.myY;
    m13 = at.myX; m23 = at.myY; m33 = at.myZ; m43 = pos.myZ;
    m14 = 0.0f; m24 = 0.0f; m34 = 0.0f; m44 = 1.0f;
}

void MyMatrix::SetAxesWorld(const Vector3Float& right, const Vector3Float& up, const Vector3Float& at, const Vector3Float& pos)
{
    m11 = right.myX; m21 = up.myX; m31 = at.myX; m41 = pos.myX;
    m12 = right.myY; m22 = up.myY; m32 = at.myY; m42 = pos.myY;
    m13 = right.myZ; m23 = up.myZ; m33 = at.myZ; m43 = pos.myZ;
    m14 = 0.0f; m24 = 0.0f; m34 = 0.0f; m44 = 1.0f;
}

void MyMatrix::SetTranslation(Vector3Float pos)
{
    m41 = pos.myX;
    m42 = pos.myY;
    m43 = pos.myZ;
}

void MyMatrix::SetTranslation(float x, float y, float z)
{
    m41 = x;
    m42 = y;
    m43 = z;
}

void MyMatrix::CreateScale(float scale)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
    m11 = m22 = m33 = scale;
    m44 = 1;
}

void MyMatrix::CreateScale(float x, float y, float z)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
    m11 = x;
    m22 = y;
    m33 = z;
    m44 = 1;
}

void MyMatrix::CreateScale(Vector3Float scale)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
    m11 = scale.myX;
    m22 = scale.myY;
    m33 = scale.myZ;
    m44 = 1;
}

void MyMatrix::CreateTranslation(float x, float y, float z)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0;
    m11 = m22 = m33 = m44 = 1;
    m41 = x;
    m42 = y;
    m43 = z;
}

void MyMatrix::CreateTranslation(Vector3Float pos)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0;
    m11 = m22 = m33 = m44 = 1;
    m41 = pos.myX;
    m42 = pos.myY;
    m43 = pos.myZ;
}

void MyMatrix::CreateSRT(float scale, Vector3Float rot, Vector3Float pos)
{
    SetIdentity();
    Scale(scale);
    Rotate(rot.myZ, 0, 0, 1); // roll
    Rotate(rot.myX, 1, 0, 0); // pitch
    Rotate(rot.myY, 0, 1, 0); // yaw
    Translate(pos.myX, pos.myY, pos.myZ);
}

void MyMatrix::CreateSRT(Vector3Float scale, Vector3Float rot, Vector3Float pos)
{
    CreateScale(scale.myX, scale.myY, scale.myZ);
    Rotate(rot.myZ, 0, 0, 1); // roll
    Rotate(rot.myX, 1, 0, 0); // pitch
    Rotate(rot.myY, 0, 1, 0); // yaw
    Translate(pos.myX, pos.myY, pos.myZ);
}

void MyMatrix::Scale(float scale)
{
    m11 *= scale; m21 *= scale; m31 *= scale; m41 *= scale;
    m12 *= scale; m22 *= scale; m32 *= scale; m42 *= scale;
    m13 *= scale; m23 *= scale; m33 *= scale; m43 *= scale;
}

void MyMatrix::Scale(float sx, float sy, float sz)
{
    m11 *= sx; m21 *= sx; m31 *= sx; m41 *= sx;
    m12 *= sy; m22 *= sy; m32 *= sy; m42 *= sy;
    m13 *= sz; m32 *= sz; m33 *= sz; m43 *= sz;
}

void MyMatrix::Rotate(float angle, float x, float y, float z)
{
    const float mag = sqrtf(x * x + y * y + z * z);
    const float sinAngle = sinf(angle * PI / 180.0f);
    const float cosAngle = cosf(angle * PI / 180.0f);
    if (mag > 0.0f)
    {
        x /= mag;
        y /= mag;
        z /= mag;

        const float xx = x * x;
        const float yy = y * y;
        const float zz = z * z;
        const float xy = x * y;
        const float yz = y * z;
        const float zx = z * x;
        const float xs = x * sinAngle;
        const float ys = y * sinAngle;
        const float zs = z * sinAngle;
        const float oneMinusCos = 1.0f - cosAngle;

        MyMatrix rotMat;
        rotMat.m11 = (oneMinusCos * xx) + cosAngle;
        rotMat.m12 = (oneMinusCos * xy) - zs;
        rotMat.m13 = (oneMinusCos * zx) + ys;
        rotMat.m14 = 0.0f;

        rotMat.m21 = (oneMinusCos * xy) + zs;
        rotMat.m22 = (oneMinusCos * yy) + cosAngle;
        rotMat.m23 = (oneMinusCos * yz) - xs;
        rotMat.m24 = 0.0f;

        rotMat.m31 = (oneMinusCos * zx) - ys;
        rotMat.m32 = (oneMinusCos * yz) + xs;
        rotMat.m33 = (oneMinusCos * zz) + cosAngle;
        rotMat.m34 = 0.0f;

        rotMat.m41 = 0.0f;
        rotMat.m42 = 0.0f;
        rotMat.m43 = 0.0f;
        rotMat.m44 = 1.0f;

        *this = rotMat * *this;
    }
}

void MyMatrix::TranslatePreRotScale(Vector3Float translate)
{
    m41 += m11 * translate.myX + m21 * translate.myY + m31 * translate.myZ;
    m42 += m12 * translate.myX + m22 * translate.myY + m32 * translate.myZ;
    m43 += m13 * translate.myX + m23 * translate.myY + m33 * translate.myZ;
    m44 += m14 * translate.myX + m24 * translate.myY + m34 * translate.myZ;
}

void MyMatrix::TranslatePreRotScale(float tx, float ty, float tz)
{
    m41 += m11 * tx + m21 * ty + m31 * tz;
    m42 += m12 * tx + m22 * ty + m32 * tz;
    m43 += m13 * tx + m23 * ty + m33 * tz;
    m44 += m14 * tx + m24 * ty + m34 * tz;
}

void MyMatrix::Translate(Vector3Float pos)
{
    m41 += pos.myX;
    m42 += pos.myY;
    m43 += pos.myZ;
}

void MyMatrix::Translate(float x, float y, float z)
{
    m41 += x;
    m42 += y;
    m43 += z;
}

void MyMatrix::CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    const float deltaX = right - left;
    const float deltaY = top - bottom;
    const float deltaZ = farZ - nearZ;

    assert(nearZ > 0.0f && farZ > 0.0f && deltaX > 0.0f && deltaY > 0.0f && deltaZ > 0.0f);

    m11 = 2.0f * nearZ / deltaX;
    m12 = m13 = m14 = 0.0f;

    m22 = 2.0f * nearZ / deltaY;
    m21 = m23 = m24 = 0.0f;

    m31 = (right + left) / deltaX;
    m32 = (top + bottom) / deltaY;
    m33 = (nearZ + farZ) / deltaZ;
    m34 = 1.0f;

    m43 = -2.0f * nearZ * farZ / deltaZ;
    m41 = m42 = m44 = 0.0f;
}

void MyMatrix::CreatePerspectiveVFoV(float halfvertfovdegrees, float aspect, float nearZ, float farZ)
{
    const GLfloat frustumTop = tanf(halfvertfovdegrees / 360.0f * PI) * nearZ;
    const GLfloat frustumRight = frustumTop * aspect;
    CreateFrustum(-frustumRight, frustumRight, -frustumTop, frustumTop, nearZ, farZ);
}

void MyMatrix::CreatePerspectiveHFoV(float halfhorfovdegrees, float aspect, float nearZ, float farZ)
{
    const GLfloat frustumRight = tanf(halfhorfovdegrees / 360.0f * PI) * nearZ;
    const GLfloat frustumTop = frustumRight / aspect;
    CreateFrustum(-frustumRight, frustumRight, -frustumTop, frustumTop, nearZ, farZ);
}

void MyMatrix::CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    const float deltaX = (right - left);
    const float deltaY = (top - bottom);
    const float deltaZ = (farZ - nearZ);

    assert((deltaX != 0.0f) && (deltaY != 0.0f) && (deltaZ != 0.0f));

    m11 = 2.0f / deltaX;
    m12 = m13 = m14 = 0;

    m22 = 2.0f / deltaY;
    m21 = m23 = m24 = 0;

    m33 = -2.0f / deltaZ;
    m31 = m32 = m34 = 0;

    m41 = -(right + left) / deltaX;
    m42 = -(top + bottom) / deltaY;
    m43 = -(farZ + nearZ) / deltaZ;
    m44 = 1;
}

void MyMatrix::CreateLookAtViewLeftHanded(const Vector3Float& eye, const Vector3Float& up, const Vector3Float& at)
{
    const Vector3Float zaxis = (at - eye).Normalize();
    const Vector3Float xaxis = (up.Cross(zaxis)).Normalize();
    const Vector3Float yaxis = zaxis.Cross(xaxis);
    const Vector3Float pos = Vector3Float(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye));
    SetAxesView(xaxis, yaxis, zaxis, pos);
}

void MyMatrix::CreateLookAtView(const Vector3Float& eye, const Vector3Float& up, const Vector3Float& at)
{
    const Vector3Float zaxis = (eye - at).Normalize();
    const Vector3Float xaxis = (up.Cross(zaxis)).Normalize();
    const Vector3Float yaxis = zaxis.Cross(xaxis);
    const Vector3Float pos = Vector3Float(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye));
    SetAxesView(xaxis, yaxis, zaxis, pos);
}

void MyMatrix::CreateLookAtWorld(const Vector3Float& anObjectPosition, const Vector3Float& up, const Vector3Float& at)
{
    const Vector3Float zaxis = (at - anObjectPosition).Normalize();
    const Vector3Float xaxis = (up.Cross(zaxis)).Normalize();
    const Vector3Float yaxis = zaxis.Cross(xaxis);
    SetAxesWorld(xaxis, yaxis, zaxis, anObjectPosition);
}

Vector3Float MyMatrix::GetEulerAngles() const
{
    if (m32 > 1.0f - epsilonFloat) // Not a unique solution: thetaZ - thetaY = atan2( -m21, m11 )
    {
        constexpr float x = PI / 2.0f;
        const float y = atan2f(m21, m11);
        constexpr float z = 0.0f;
        return Vector3Float(x, y, z);
    }

    if (m32 < -1.0f + epsilonFloat) // Not a unique solution: thetaZ + thetaY = atan2( -m21, m11 )
    {
        constexpr float x = -PI / 2.0f;
        const float y = -atan2f(m21, m11);
        constexpr float z = 0.0f;
        return Vector3Float(x, y, z);
    }

    const float x = asinf(m32);
    const float y = atan2f(-m31, m33);
    const float z = atan2f(-m12, m22);
    return Vector3Float(x, y, z);
}

Vector3Float MyMatrix::GetScale() const
{
    Vector3Float scale;
    scale.myX = Vector3Float(m11, m12, m13).Length();
    scale.myY = Vector3Float(m21, m22, m23).Length();
    scale.myZ = Vector3Float(m31, m32, m33).Length();
    return scale;
}

Vector3Float MyMatrix::GetUp() const
{
    return Vector3Float(m21, m22, m23);
}

Vector3Float MyMatrix::GetRight() const
{
    return Vector3Float(m11, m12, m13);
}

Vector3Float MyMatrix::GetAt() const
{
    return Vector3Float(m31, m32, m33);
}

MyMatrix MyMatrix::GetInverse(float tolerance) const
{
    MyMatrix invmat = *this;
    invmat.Inverse(tolerance);
    return invmat;
}
