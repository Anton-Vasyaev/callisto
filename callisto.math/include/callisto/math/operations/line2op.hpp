#pragma once

#include <cstdint>
#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct line2op
{
    template<typename line1_type, typename line2_type>
    static constexpr auto
    cross_point(const line1_type& line1, const line2_type& line2, double eps = 1e-8) noexcept
    {
        double x1 = line1.start.x;
        double y1 = line1.start.y;

        double x2 = line1.end.x;
        double y2 = line1.end.y;

        double x3 = line2.start.x;
        double y3 = line2.start.y;

        double x4 = line2.end.x;
        double y4 = line2.end.y;

        double x_num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
        double y_num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

        double div = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        double x = x_num / (div + eps);
        double y = y_num / (div + eps);

        return point2d(x, y);
    }

    template<typename line_type>
    static constexpr auto get_contour(const line_type& line) noexcept
    {
        auto left  = std::min(line.x1, line.x2);
        auto right = std::max(line.x1, line.x2);

        auto top    = std::min(line.y1, line.y2);
        auto bottom = std::max(line.y1, line.y2);

        return bbox2(left, top, right, bottom);
    }
};

} // namespace callisto::math