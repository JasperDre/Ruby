#pragma once

#include <cmath>

#define PI 3.14159265358979323846f

static constexpr double epsilonDouble = std::numeric_limits<double>::epsilon();
static constexpr float epsilonFloat = std::numeric_limits<float>::epsilon();

inline bool IsEqualFloat(const float a, const float b, const float epsilon = epsilonFloat)
{
    return std::abs(a - b) <= epsilon;
}

inline bool IsNotEqualFloat(const float a, const float b, const float epsilon = epsilonFloat)
{
    return std::abs(a - b) > epsilon;
}

template<class MyType> void MySwap(MyType& v1, MyType& v2)
{
    MyType temp = v1;
    v1 = v2;
    v2 = temp;
}

template<class MyType> void MyClamp(MyType& value, MyType min, MyType max)
{
    if (value < min)
        value = min;

    if (value > max)
        value = max;
}

template<class MyType> MyType MyClamp_Return(MyType value, MyType min, MyType max)
{
    MyType temp = value;

    if (temp < min)
        temp = min;

    if (temp > max)
        temp = max;

    return temp;
}

template<class MyType> void IncreaseIfBigger(MyType& value, MyType newvalue)
{
    if (newvalue > value)
        value = newvalue;
}

template<class MyType> void DecreaseIfLower(MyType& value, MyType newvalue, bool treatzeroasinfinite = false)
{
    if (treatzeroasinfinite && value == 0)
        value = newvalue;

    if (newvalue < value)
        value = newvalue;
}

inline float randFromNegativeOneToOne()
{
    return rand() % 20000 / 10000.0f - 1.0f;
}

inline bool IsClose(float a, float b, float aRange)
{
    if (a - b < aRange && a < b + aRange)
        return true;

    return false;
}