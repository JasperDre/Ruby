#pragma once

#include "Math/MathConstants.h"

namespace MathUtility
{
    int GetRandomInteger();
    int GetRandomRangeInteger(int aMin, int aMax);
    bool IsEqualFloat(float a, float b, float epsilon = Math::epsilonFloat);
    bool IsNotEqualFloat(float a, float b, float epsilon = Math::epsilonFloat);
    bool IsClose(float a, float b, float aRange);

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
}