#pragma once

// std
#include <cmath>
#include <span>
// project
#include <callisto/math/operations/vector2op.hpp>
#include <callisto/math/functions.hpp>
#include <callisto/math/error.hpp>

namespace callisto::math
{

struct poly2op
{
    template<
        typename type,
        typename calc_type = std::conditional_t<std::is_same_v<type, double>, double, float>>
    static auto area(std::span<point2<type>> polygon) noexcept
    {
        auto n = polygon.size();

        calc_type first_sum = 0.0;
        calc_type y1        = polygon[0].y;
        calc_type xn        = polygon[n - 1].x;

        for (int64_t i = 0; i < n - 1; i++)
        {
            calc_type x_i   = polygon[i].x;
            calc_type y_ip1 = polygon[i + 1].y;

            first_sum += x_i * y_ip1;
        }
        first_sum += xn * y1;

        calc_type second_sum = 0.0;
        calc_type x1         = polygon[0].x;
        calc_type yn         = polygon[n - 1].y;
        for (int64_t i = 0; i < n - 1; i++)
        {
            calc_type x_ip1 = polygon[i + 1].x;
            calc_type y_i   = polygon[i].y;

            second_sum += x_ip1 * y_i;
        }
        second_sum += x1 * yn;

        const calc_type poly_area = std::abs(first_sum - second_sum) / 2;

        return poly_area;
    }

    template<
        typename type,
        typename calc_type = std::conditional_t<std::is_same_v<type, double>, double, float>>
    static bool contain(
        std::span<point2<type>> polygon,
        const point2<type>&     point,
        calc_type               eps = 1e-3
    ) noexcept
    {
        calc_type sum_of_angles = 0.0;

        auto prev_poly_point = polygon[polygon.size() - 1];

        for (auto& curr_poly_point : polygon)
        {
            auto prev_vec = prev_poly_point - point;
            auto curr_vec = curr_poly_point - point;

            sum_of_angles += vector2op::sign_angle(prev_vec, curr_vec);

            prev_poly_point = curr_poly_point;
        }

        sum_of_angles = rad2deg(sum_of_angles);

        return relative_error(sum_of_angles, eps) == 360.0;
    }
};
} // namespace callisto::math