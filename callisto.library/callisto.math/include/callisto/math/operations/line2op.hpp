#pragma once

#include <cstdint>
#include <algorithm>
#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct line2op
{
    template<typename type_1, typename type_2>
    static constexpr auto
    cross_point(const line2<type_1>& line1, const line2<type_2>& line2, double eps = 1e-8) noexcept
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

    template<typename type>
    inline static constexpr auto get_contour(const line2<type>& line) noexcept
    {
        auto [left, right] = std::minmax(line.x1, line.x2);
        auto [top, bottom] = std::minmax(line.y1, line.y2);

        return bbox2<type>(left, top, right, bottom);
    }

    template<typename line_type, typename bbox_type>
    inline static constexpr auto normalize(const line2<line_type>& line, const bbox2<bbox_type>& contour)
    {
        auto w = contour.width();
        auto h = contour.height();

        auto x1 = line.x1;
        auto y1 = line.y1;

        auto x2 = line.x2;
        auto y2 = line.y2;

        auto norm_x1 = (x1 - contour.x1) / w;
        auto norm_y1 = (y1 - contour.y1) / h;

        auto norm_x2 = (x2 - contour.x1) / w;
        auto norm_y2 = (y2 - contour.y1) / h;

        return line2<decltype(norm_x1)>(norm_x1, norm_y1, norm_x2, norm_y2);
    }
};

} // namespace callisto::math