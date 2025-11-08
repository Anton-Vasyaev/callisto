#pragma once

#include "constants.hpp"

namespace callisto::math
{

constexpr double radian_to_degree(double radians) { return radians * degree_per_radian; }

constexpr double degree_to_radian(double degrees) { return degrees * radian_per_degree; }

} // namespace callisto::math