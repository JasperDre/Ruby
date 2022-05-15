#pragma once

#include "Vector4Float.h"

// Values are stored column major.
// m11 m21 m31 m41       Sx  0  0 Tx
// m12 m22 m32 m42  --\   0 Sy  0 Ty
// m13 m23 m33 m43  --/   0  0 Sz Tz
// m14 m24 m34 m44        0  0  0  1
class Matrix4Float
{
public:

    Matrix4Float() : m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f), m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f), m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f), m41(0.0f), m42(0.0f), m43(0.0f), m44(0.0f) {}
    Matrix4Float(float v11, float v12, float v13, float v14,
             float v21, float v22, float v23, float v24,
             float v31, float v32, float v33, float v34,
             float v41, float v42, float v43, float v44)
        : m11(v11), m12(v21), m13(v31), m14(v41)
        , m21(v12), m22(v22), m23(v32), m24(v42)
        , m31(v13), m32(v23), m33(v33), m34(v43)
        , m41(v14), m42(v24), m43(v34), m44(v44) {}

    void Scale(float scale);
    void Scale(float sx, float sy, float sz);
    void Rotate(float angle, float x, float y, float z);
    void TranslatePreRotScale(Vector3Float translate);
    void TranslatePreRotScale(float tx, float ty, float tz);
    void Translate(Vector3Float pos);
    void Translate(float x, float y, float z);

    void SetIdentity();
    void SetAxesView(const Vector3Float& right, const Vector3Float& up, const Vector3Float& at, const Vector3Float& pos);
    void SetAxesWorld(const Vector3Float& right, const Vector3Float& up, const Vector3Float& at, const Vector3Float& pos);
    void SetTranslation(Vector3Float pos);
    void SetTranslation(float x, float y, float z);
    void CreateScale(float scale);
    void CreateScale(float x, float y, float z);
    void CreateScale(Vector3Float scale);
    void CreateTranslation(float x, float y, float z);
    void CreateTranslation(Vector3Float pos);
    void CreateSRT(float scale, Vector3Float rot, Vector3Float pos);
    void CreateSRT(Vector3Float scale, Vector3Float rot, Vector3Float pos);
    void CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    void CreatePerspectiveVFoV(float halfvertfovdegrees, float aspect, float nearZ, float farZ);
    void CreatePerspectiveHFoV(float halfhorfovdegrees, float aspect, float nearZ, float farZ);
    void CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
    void CreateLookAtViewLeftHanded(const Vector3Float& eye, const Vector3Float& up, const Vector3Float& at);
    void CreateLookAtView(const Vector3Float& eye, const Vector3Float& up, const Vector3Float& at);
    void CreateLookAtWorld(const Vector3Float& anObjectPosition, const Vector3Float& up, const Vector3Float& at);

    [[nodiscard]] Vector3Float GetTranslation() const { return Vector3Float(m41, m42, m43); }
    [[nodiscard]] Vector3Float GetEulerAngles() const;
    [[nodiscard]] Vector3Float GetScale() const;
    [[nodiscard]] Vector3Float GetUp() const;
    [[nodiscard]] Vector3Float GetRight() const;
    [[nodiscard]] Vector3Float GetAt() const;

    void Transpose()
    {
        float temp = m12; m12 = m21; m21 = temp;
        temp = m13; m13 = m31; m31 = temp;
        temp = m14; m14 = m41; m41 = temp;
        temp = m23; m23 = m32; m32 = temp;
        temp = m24; m24 = m42; m42 = temp;
        temp = m34; m34 = m43; m43 = temp;
    }

    Matrix4Float operator *(const float o) const
    {
        Matrix4Float newmat;

        newmat.m11 = m11 * o; newmat.m21 = m21 * o; newmat.m31 = m31 * o; newmat.m41 = m41 * o;
        newmat.m12 = m12 * o; newmat.m22 = m22 * o; newmat.m32 = m32 * o; newmat.m42 = m42 * o;
        newmat.m13 = m13 * o; newmat.m23 = m23 * o; newmat.m33 = m33 * o; newmat.m43 = m43 * o;
        newmat.m14 = m14 * o; newmat.m24 = m24 * o; newmat.m34 = m34 * o; newmat.m44 = m44 * o;

        return newmat;
    }

    Vector2Float operator *(const Vector2Float o) const
    {
        const Vector4Float result = Vector4Float(m11 * o.myX + m21 * o.myY + 0.0f + m41 * 1.0f,
                                        m12 * o.myX + m22 * o.myY + 0.0f + m42 * 1.0f,
                                        m13 * o.myX + m23 * o.myY + 0.0f + m43 * 1.0f,
                                        m14 * o.myX + m24 * o.myY + 0.0f + m44 * 1.0f);
        if (result.myW > 0.0f)
            return Vector2Float(result.myX / result.myW, result.myY / result.myW);

        return Vector2Float(result.myX, result.myY);
    }

    Vector3Float operator *(const Vector3Float o) const
    {
        const Vector4Float result = Vector4Float(m11 * o.myX + m21 * o.myY + m31 * o.myZ + m41 * 1.0f,
                                        m12 * o.myX + m22 * o.myY + m32 * o.myZ + m42 * 1.0f,
                                        m13 * o.myX + m23 * o.myY + m33 * o.myZ + m43 * 1.0f,
                                        m14 * o.myX + m24 * o.myY + m34 * o.myZ + m44 * 1.0f);
        if (result.myW > 0.0f)
            return Vector3Float(result.myX / result.myW, result.myY / result.myW, result.myZ / result.myW);

        return Vector3Float(result.myX, result.myY, result.myZ);
    }

    Vector4Float operator *(const Vector4Float o) const
    {
        return Vector4Float(m11 * o.myX + m21 * o.myY + m31 * o.myZ + m41 * o.myW,
                        m12 * o.myX + m22 * o.myY + m32 * o.myZ + m42 * o.myW,
                        m13 * o.myX + m23 * o.myY + m33 * o.myZ + m43 * o.myW,
                        m14 * o.myX + m24 * o.myY + m34 * o.myZ + m44 * o.myW);
    }

    Matrix4Float operator *(const Matrix4Float o) const
    {
        Matrix4Float newmat;

        newmat.m11 = m11 * o.m11 + m21 * o.m12 + m31 * o.m13 + m41 * o.m14;
        newmat.m12 = m12 * o.m11 + m22 * o.m12 + m32 * o.m13 + m42 * o.m14;
        newmat.m13 = m13 * o.m11 + m23 * o.m12 + m33 * o.m13 + m43 * o.m14;
        newmat.m14 = m14 * o.m11 + m24 * o.m12 + m34 * o.m13 + m44 * o.m14;
        newmat.m21 = m11 * o.m21 + m21 * o.m22 + m31 * o.m23 + m41 * o.m24;
        newmat.m22 = m12 * o.m21 + m22 * o.m22 + m32 * o.m23 + m42 * o.m24;
        newmat.m23 = m13 * o.m21 + m23 * o.m22 + m33 * o.m23 + m43 * o.m24;
        newmat.m24 = m14 * o.m21 + m24 * o.m22 + m34 * o.m23 + m44 * o.m24;
        newmat.m31 = m11 * o.m31 + m21 * o.m32 + m31 * o.m33 + m41 * o.m34;
        newmat.m32 = m12 * o.m31 + m22 * o.m32 + m32 * o.m33 + m42 * o.m34;
        newmat.m33 = m13 * o.m31 + m23 * o.m32 + m33 * o.m33 + m43 * o.m34;
        newmat.m34 = m14 * o.m31 + m24 * o.m32 + m34 * o.m33 + m44 * o.m34;
        newmat.m41 = m11 * o.m41 + m21 * o.m42 + m31 * o.m43 + m41 * o.m44;
        newmat.m42 = m12 * o.m41 + m22 * o.m42 + m32 * o.m43 + m42 * o.m44;
        newmat.m43 = m13 * o.m41 + m23 * o.m42 + m33 * o.m43 + m43 * o.m44;
        newmat.m44 = m14 * o.m41 + m24 * o.m42 + m34 * o.m43 + m44 * o.m44;

        return newmat;
    }

    bool Inverse(float tolerance = 0.0001f);

    [[nodiscard]] Matrix4Float GetInverse(float tolerance = 0.0001f) const;

    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
};