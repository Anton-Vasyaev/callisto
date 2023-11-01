#pragma once

// std
#include <cmath>

namespace callisto::opencv
{

void hsv2rgb(double h, double s, double v, double& r, double& g, double& b);

} // namespace callisto::opencv