#pragma once

#include <cstdint>
#include <algorithm>
#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct line2op
{
    template<typename line1_type, typename line2_type>
    static constexpr auto
    cross_point(const line1_type& line1, const line2_type& line2, double eps = 1e-8) noexcept
    {
        double x1 = line1.x1;
        double y1 = line1.y1;

        double x2 = line1.x2;
        double y2 = line1.y2;

        double x3 = line2.x1;
        double y3 = line2.y1;

        double x4 = line2.x2;
        double y4 = line2.y2;

        double x_num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
        double y_num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

        double div = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        double x = x_num / (div + eps);
        double y = y_num / (div + eps);

        return point2d(x, y);
    }

    template<typename line_type>
    static constexpr auto get_bbox(const line_type& line) noexcept
    {
        auto [left, right] = std::minmax(line.x1, line.x2);
        auto [top, bottom] = std::minmax(line.y1, line.y2);

        return bbox2(left, top, right, bottom);
    }
};

} // namespace callisto::math