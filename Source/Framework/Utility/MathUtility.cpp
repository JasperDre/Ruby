#include "FrameworkPCH.h"
#include "MathUtility.h"

namespace MathUtility
{
	int GetRandomInteger()
	{
		return GetRandomRangeInteger(0, UINT_MAX);
	}

	int GetRandomRangeInteger(int aMin, int aMax)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		const std::uniform_int_distribution<int> distribution(aMin, aMax);

		return distribution(generator);
	}

	bool IsEqualFloat(float a, float b, float epsilon)
	{
		return std::abs(a - b) <= epsilon;
	}

	bool IsNotEqualFloat(float a, float b, float epsilon)
	{
		    return std::abs(a - b) > epsilon;
	}

	bool IsClose(float a, float b, float aRange)
	{
		if (a - b < aRange && a < b + aRange)
			return true;

		return false;
	}
}
