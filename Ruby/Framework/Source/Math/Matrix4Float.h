#pragma once

#include "Vector.h"

// Values are stored column major.
// m11 m21 m31 m41       Sx  0  0 Tx
// m12 m22 m32 m42  --\   0 Sy  0 Ty
// m13 m23 m33 m43  --/   0  0 Sz Tz
// m14 m24 m34 m44        0  0  0  1
class MyMatrix
{
public:

    MyMatrix() : m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f), m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f), m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f), m41(0.0f), m42(0.0f), m43(0.0f), m44(0.0f) {}
    MyMatrix(float v11, float v12, float v13, float v14,
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

    MyMatrix operator *(const float o) const
    {
        MyMatrix newmat;

        newmat.m11 = this->m11 * o; newmat.m21 = this->m21 * o; newmat.m31 = this->m31 * o; newmat.m41 = this->m41 * o;
        newmat.m12 = this->m12 * o; newmat.m22 = this->m22 * o; newmat.m32 = this->m32 * o; newmat.m42 = this->m42 * o;
        newmat.m13 = this->m13 * o; newmat.m23 = this->m23 * o; newmat.m33 = this->m33 * o; newmat.m43 = this->m43 * o;
        newmat.m14 = this->m14 * o; newmat.m24 = this->m24 * o; newmat.m34 = this->m34 * o; newmat.m44 = this->m44 * o;

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

    MyMatrix operator *(const MyMatrix o) const
    {
        MyMatrix newmat;

        newmat.m11 = this->m11 * o.m11 + this->m21 * o.m12 + this->m31 * o.m13 + this->m41 * o.m14;
        newmat.m12 = this->m12 * o.m11 + this->m22 * o.m12 + this->m32 * o.m13 + this->m42 * o.m14;
        newmat.m13 = this->m13 * o.m11 + this->m23 * o.m12 + this->m33 * o.m13 + this->m43 * o.m14;
        newmat.m14 = this->m14 * o.m11 + this->m24 * o.m12 + this->m34 * o.m13 + this->m44 * o.m14;
        newmat.m21 = this->m11 * o.m21 + this->m21 * o.m22 + this->m31 * o.m23 + this->m41 * o.m24;
        newmat.m22 = this->m12 * o.m21 + this->m22 * o.m22 + this->m32 * o.m23 + this->m42 * o.m24;
        newmat.m23 = this->m13 * o.m21 + this->m23 * o.m22 + this->m33 * o.m23 + this->m43 * o.m24;
        newmat.m24 = this->m14 * o.m21 + this->m24 * o.m22 + this->m34 * o.m23 + this->m44 * o.m24;
        newmat.m31 = this->m11 * o.m31 + this->m21 * o.m32 + this->m31 * o.m33 + this->m41 * o.m34;
        newmat.m32 = this->m12 * o.m31 + this->m22 * o.m32 + this->m32 * o.m33 + this->m42 * o.m34;
        newmat.m33 = this->m13 * o.m31 + this->m23 * o.m32 + this->m33 * o.m33 + this->m43 * o.m34;
        newmat.m34 = this->m14 * o.m31 + this->m24 * o.m32 + this->m34 * o.m33 + this->m44 * o.m34;
        newmat.m41 = this->m11 * o.m41 + this->m21 * o.m42 + this->m31 * o.m43 + this->m41 * o.m44;
        newmat.m42 = this->m12 * o.m41 + this->m22 * o.m42 + this->m32 * o.m43 + this->m42 * o.m44;
        newmat.m43 = this->m13 * o.m41 + this->m23 * o.m42 + this->m33 * o.m43 + this->m43 * o.m44;
        newmat.m44 = this->m14 * o.m41 + this->m24 * o.m42 + this->m34 * o.m43 + this->m44 * o.m44;

        return newmat;
    }

    bool Inverse(float tolerance = 0.0001f)
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
        if (fabs(det) <= tolerance)
            return false;

        // Compute adjugate matrix
        *this = MyMatrix(
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

    [[nodiscard]] MyMatrix GetInverse(float tolerance = 0.0001f) const;

    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
};