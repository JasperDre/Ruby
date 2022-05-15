#pragma once

#include <limits>

namespace Math
{
	static constexpr float pi = 3.14159265358979323846f;
	static constexpr double epsilonDouble = std::numeric_limits<double>::epsilon();
	static constexpr float epsilonFloat = std::numeric_limits<float>::epsilon();
}
