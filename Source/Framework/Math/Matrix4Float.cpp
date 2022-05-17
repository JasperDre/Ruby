#include "Matrix4Float.h"

#include <cassert>
#include <cmath>

#include "MathConstants.h"

void Matrix4Float::SetIdentity()
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0f;
    m11 = m22 = m33 = m44 = 1.0f;
}

void Matrix4Float::SetAxesView(const Vector3Float& right, const Vector3Float& up, const Vector3Float& at, const Vector3Float& pos)
{
    m11 = right.myX; m21 = right.myY; m31 = right.myZ; m41 = pos.myX;
    m12 = up.myX; m22 = up.myY; m32 = up.myZ; m42 = pos.myY;
    m13 = at.myX; m23 = at.myY; m33 = at.myZ; m43 = pos.myZ;
    m14 = 0.0f; m24 = 0.0f; m34 = 0.0f; m44 = 1.0f;
}

void Matrix4Float::SetAxesWorld(const Vector3Float& right, const Vector3Float& up, const Vector3Float& at, const Vector3Float& pos)
{
    m11 = right.myX; m21 = up.myX; m31 = at.myX; m41 = pos.myX;
    m12 = right.myY; m22 = up.myY; m32 = at.myY; m42 = pos.myY;
    m13 = right.myZ; m23 = up.myZ; m33 = at.myZ; m43 = pos.myZ;
    m14 = 0.0f; m24 = 0.0f; m34 = 0.0f; m44 = 1.0f;
}

void Matrix4Float::SetTranslation(Vector3Float pos)
{
    m41 = pos.myX;
    m42 = pos.myY;
    m43 = pos.myZ;
}

void Matrix4Float::SetTranslation(float x, float y, float z)
{
    m41 = x;
    m42 = y;
    m43 = z;
}

void Matrix4Float::CreateScale(float scale)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0f;
    m11 = m22 = m33 = scale;
    m44 = 1.0f;
}

void Matrix4Float::CreateScale(float x, float y, float z)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0f;
    m11 = x;
    m22 = y;
    m33 = z;
    m44 = 1;
}

void Matrix4Float::CreateScale(Vector3Float scale)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0f;
    m11 = scale.myX;
    m22 = scale.myY;
    m33 = scale.myZ;
    m44 = 1.0f;
}

void Matrix4Float::CreateTranslation(float x, float y, float z)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0.0f;
    m11 = m22 = m33 = m44 = 1.0f;
    m41 = x;
    m42 = y;
    m43 = z;
}

void Matrix4Float::CreateTranslation(Vector3Float pos)
{
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0.0f;
    m11 = m22 = m33 = m44 = 1.0f;
    m41 = pos.myX;
    m42 = pos.myY;
    m43 = pos.myZ;
}

void Matrix4Float::CreateSRT(float scale, Vector3Float rot, Vector3Float pos)
{
    SetIdentity();
    Scale(scale);
    Rotate(rot.myZ, 0.0f, 0.0f, 1.0f); // roll
    Rotate(rot.myX, 1.0f, 0.0f, 0.0f); // pitch
    Rotate(rot.myY, 0.0f, 1.0f, 0.0f); // yaw
    Translate(pos.myX, pos.myY, pos.myZ);
}

void Matrix4Float::CreateSRT(Vector3Float scale, Vector3Float rot, Vector3Float pos)
{
    CreateScale(scale.myX, scale.myY, scale.myZ);
    Rotate(rot.myZ, 0.0f, 0.0f, 1.0f); // roll
    Rotate(rot.myX, 1.0f, 0.0f, 0.0f); // pitch
    Rotate(rot.myY, 0.0f, 1.0f, 0.0f); // yaw
    Translate(pos.myX, pos.myY, pos.myZ);
}

void Matrix4Float::Scale(float scale)
{
    m11 *= scale; m21 *= scale; m31 *= scale; m41 *= scale;
    m12 *= scale; m22 *= scale; m32 *= scale; m42 *= scale;
    m13 *= scale; m23 *= scale; m33 *= scale; m43 *= scale;
}

void Matrix4Float::Scale(float sx, float sy, float sz)
{
    m11 *= sx; m21 *= sx; m31 *= sx; m41 *= sx;
    m12 *= sy; m22 *= sy; m32 *= sy; m42 *= sy;
    m13 *= sz; m32 *= sz; m33 *= sz; m43 *= sz;
}

void Matrix4Float::Rotate(float angle, float x, float y, float z)
{
    const float mag = std::sqrtf(x * x + y * y + z * z);
    const float sinAngle = sinf(angle * Math::pi / 180.0f);
    const float cosAngle = cosf(angle * Math::pi / 180.0f);
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

        Matrix4Float rotMat;
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

void Matrix4Float::TranslatePreRotScale(Vector3Float translate)
{
    m41 += m11 * translate.myX + m21 * translate.myY + m31 * translate.myZ;
    m42 += m12 * translate.myX + m22 * translate.myY + m32 * translate.myZ;
    m43 += m13 * translate.myX + m23 * translate.myY + m33 * translate.myZ;
    m44 += m14 * translate.myX + m24 * translate.myY + m34 * translate.myZ;
}

void Matrix4Float::TranslatePreRotScale(float tx, float ty, float tz)
{
    m41 += m11 * tx + m21 * ty + m31 * tz;
    m42 += m12 * tx + m22 * ty + m32 * tz;
    m43 += m13 * tx + m23 * ty + m33 * tz;
    m44 += m14 * tx + m24 * ty + m34 * tz;
}

void Matrix4Float::Translate(Vector3Float pos)
{
    m41 += pos.myX;
    m42 += pos.myY;
    m43 += pos.myZ;
}

void Matrix4Float::Translate(float x, float y, float z)
{
    m41 += x;
    m42 += y;
    m43 += z;
}

void Matrix4Float::CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
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

void Matrix4Float::CreatePerspectiveVFoV(float halfvertfovdegrees, float aspect, float nearZ, float farZ)
{
    const float frustumTop = std::tanf(halfvertfovdegrees / 360.0f * Math::pi) * nearZ;
    const float frustumRight = frustumTop * aspect;
    CreateFrustum(-frustumRight, frustumRight, -frustumTop, frustumTop, nearZ, farZ);
}

void Matrix4Float::CreatePerspectiveHFoV(float halfhorfovdegrees, float aspect, float nearZ, float farZ)
{
    const float frustumRight = std::tanf(halfhorfovdegrees / 360.0f * Math::pi) * nearZ;
    const float frustumTop = frustumRight / aspect;
    CreateFrustum(-frustumRight, frustumRight, -frustumTop, frustumTop, nearZ, farZ);
}

void Matrix4Float::CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    const float deltaX = (right - left);
    const float deltaY = (top - bottom);
    const float deltaZ = (farZ - nearZ);

    assert((deltaX != 0.0f) && (deltaY != 0.0f) && (deltaZ != 0.0f));

    m11 = 2.0f / deltaX;
    m12 = m13 = m14 = 0.0f;

    m22 = 2.0f / deltaY;
    m21 = m23 = m24 = 0.0f;

    m33 = -2.0f / deltaZ;
    m31 = m32 = m34 = 0.0f;

    m41 = -(right + left) / deltaX;
    m42 = -(top + bottom) / deltaY;
    m43 = -(farZ + nearZ) / deltaZ;
    m44 = 1;
}

void Matrix4Float::CreateLookAtViewLeftHanded(const Vector3Float& eye, const Vector3Float& up, const Vector3Float& at)
{
    const Vector3Float zaxis = (at - eye).Normalize();
    const Vector3Float xaxis = (up.Cross(zaxis)).Normalize();
    const Vector3Float yaxis = zaxis.Cross(xaxis);
    const Vector3Float pos = Vector3Float(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye));
    SetAxesView(xaxis, yaxis, zaxis, pos);
}

void Matrix4Float::CreateLookAtView(const Vector3Float& eye, const Vector3Float& up, const Vector3Float& at)
{
    const Vector3Float zaxis = (eye - at).Normalize();
    const Vector3Float xaxis = (up.Cross(zaxis)).Normalize();
    const Vector3Float yaxis = zaxis.Cross(xaxis);
    const Vector3Float pos = Vector3Float(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye));
    SetAxesView(xaxis, yaxis, zaxis, pos);
}

void Matrix4Float::CreateLookAtWorld(const Vector3Float& anObjectPosition, const Vector3Float& up, const Vector3Float& at)
{
    const Vector3Float zaxis = (at - anObjectPosition).Normalize();
    const Vector3Float xaxis = (up.Cross(zaxis)).Normalize();
    const Vector3Float yaxis = zaxis.Cross(xaxis);
    SetAxesWorld(xaxis, yaxis, zaxis, anObjectPosition);
}

Vector3Float Matrix4Float::GetEulerAngles() const
{
    if (m32 > 1.0f - Math::epsilonFloat) // Not a unique solution: thetaZ - thetaY = atan2( -m21, m11 )
    {
        constexpr float x = Math::pi / 2.0f;
        const float y = std::atan2f(m21, m11);
        constexpr float z = 0.0f;
        return Vector3Float(x, y, z);
    }

    if (m32 < -1.0f + Math::epsilonFloat) // Not a unique solution: thetaZ + thetaY = atan2( -m21, m11 )
    {
        constexpr float x = -Math::pi / 2.0f;
        const float y = -std::atan2f(m21, m11);
        constexpr float z = 0.0f;
        return Vector3Float(x, y, z);
    }

    const float x = std::asinf(m32);
    const float y = std::atan2f(-m31, m33);
    const float z = std::atan2f(-m12, m22);
    return Vector3Float(x, y, z);
}

Vector3Float Matrix4Float::GetScale() const
{
    Vector3Float scale;
    scale.myX = Vector3Float(m11, m12, m13).Length();
    scale.myY = Vector3Float(m21, m22, m23).Length();
    scale.myZ = Vector3Float(m31, m32, m33).Length();
    return scale;
}

Vector3Float Matrix4Float::GetUp() const
{
    return Vector3Float(m21, m22, m23);
}

Vector3Float Matrix4Float::GetRight() const
{
    return Vector3Float(m11, m12, m13);
}

Vector3Float Matrix4Float::GetAt() const
{
    return Vector3Float(m31, m32, m33);
}

bool Matrix4Float::Inverse(float tolerance)
{
    // Determinants of 2x2 submatrices
    const float S0 = m11 * m22 - m12 * m21;
    const float S1 = m11 * m23 - m13 * m21;
    const float S2 = m11 * m24 - m14 * m21;
    const float S3 = m12 * m23 - m13 * m22;
    const float S4 = m12 * m24 - m14 * m22;
    const float S5 = m13 * m24 - m14 * m23;

    const float C5 = m33 * m44 - m34 * m43;
    const float C4 = m32 * m44 - m34 * m42;
    const float C3 = m32 * m43 - m33 * m42;
    const float C2 = m31 * m44 - m34 * m41;
    const float C1 = m31 * m43 - m33 * m41;
    const float C0 = m31 * m42 - m32 * m41;

    // If determinant equals 0, there is no inverse
    const float det = S0 * C5 - S1 * C4 + S2 * C3 + S3 * C2 - S4 * C1 + S5 * C0;
    if (std::fabs(det) <= tolerance)
        return false;

    // Compute adjugate matrix
    *this = Matrix4Float(
         m22 * C5 - m23 * C4 + m24 * C3, -m12 * C5 + m13 * C4 - m14 * C3,
         m42 * S5 - m43 * S4 + m44 * S3, -m32 * S5 + m33 * S4 - m34 * S3,

        -m21 * C5 + m23 * C2 - m24 * C1, m11 * C5 - m13 * C2 + m14 * C1,
        -m41 * S5 + m43 * S2 - m44 * S1, m31 * S5 - m33 * S2 + m34 * S1,

         m21 * C4 - m22 * C2 + m24 * C0, -m11 * C4 + m12 * C2 - m14 * C0,
         m41 * S4 - m42 * S2 + m44 * S0, -m31 * S4 + m32 * S2 - m34 * S0,

        -m21 * C3 + m22 * C1 - m23 * C0, m11 * C3 - m12 * C1 + m13 * C0,
        -m41 * S3 + m42 * S1 - m43 * S0, m31 * S3 - m32 * S1 + m33 * S0) * (1.0f / det);

    return true;
}

Matrix4Float Matrix4Float::GetInverse(float tolerance) const
{
    Matrix4Float invmat = *this;
    invmat.Inverse(tolerance);
    return invmat;
}
