#pragma once

// std
#include <cmath>
// project
#include <callisto/math/operations/vector2op.hpp>


namespace callisto::math
{

struct poly2op
{
    template<typename points_array_type>
    static double area(const points_array_type& polygon) noexcept
    {
        auto n = polygon.size();

        double first_sum = 0.0;
        double y1 = polygon[0].y;
        double xn = polygon[n - 1].x;

        for(int64_t i = 0; i < n - 1; i++)
        {
            double x_i = polygon[i].x;
            double y_ip1   = polygon[i + 1].y;

            first_sum += x_i * y_ip1;
        }
        first_sum += xn * y1;

        double second_sum = 0.0;
        double x1 = polygon[0].x;
        double yn = polygon[n - 1].y;
        for(int64_t i = 0; i < n - 1; i++)
        {
            double x_ip1 = polygon[i + 1].x;
            double y_i = polygon[i].y;

            second_sum += x_ip1 * y_i;
        }
        second_sum += x1 * yn;

        double poly_area = std::abs(first_sum - second_sum) / 2;

        return poly_area;
    }
};



}