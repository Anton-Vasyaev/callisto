// parent header
#include <callisto/opencv/conversion.hpp>

namespace callisto::opencv
{

void hsv2rgb(double h, double s, double v, double& r, double& g, double& b)
{
    double h_i = std::fmod(h / 60.0, 6.0);

    double v_min = (100 - s) * v / 100.0;

    double a = (v - v_min) * (std::fmod(h, 60.0) / 60.0);

    double v_inc = v_min + a;
    double v_dec = v - a;

    v     = v * 255.0 / 100.0;
    v_min = v_min * 255.0 / 100.0;
    v_inc = v_inc * 255.0 / 100.0;
    v_dec = v_dec * 255.0 / 100.0;

    if (h_i >= 0.0 && h_i < 1.0)
    {
        r = v;
        g = v_inc;
        b = v_min;
    }
    else if (h_i >= 1.0 && h_i < 2.0)
    {
        r = v_dec;
        g = v;
        b = v_min;
    }
    else if (h_i >= 2.0 && h_i < 3.0)
    {
        r = v_min;
        g = v;
        b = v_inc;
    }
    else if (h_i >= 3.0 && h_i < 4.0)
    {
        r = v_min;
        g = v_dec;
        b = v;
    }
    else if (h_i >= 4.0 && h_i < 5.0)
    {
        r = v_inc;
        g = v_min;
        b = v;
    }
    else
    {
        r = v;
        g = v_min;
        b = v_dec;
    }
}

} // namespace callisto::opencv