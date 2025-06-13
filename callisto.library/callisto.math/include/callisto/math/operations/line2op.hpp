#pragma once

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct line2op
{
    template<typename type>
    static constexpr auto
    cross_point(const line2<type>& line1, const line2<type>& line2, type eps = 1e-6) noexcept
    {
        type x1 = line1.x1;
        type y1 = line1.y1;

        type x2 = line1.x2;
        type y2 = line1.y2;

        type x3 = line2.x1;
        type y3 = line2.y1;

        type x4 = line2.x2;
        type y4 = line2.y2;

        const type x_num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
        const type y_num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

        const type div = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        const type x = x_num / (div + eps);
        const type y = y_num / (div + eps);

        return point2<type>(x, y);
    }

    template<typename type>
    static constexpr auto get_box_contour(const line2<type>& line) noexcept
    {
        auto [left, right] = std::minmax(line.x1, line.x2);
        auto [top, bottom] = std::minmax(line.y1, line.y2);

        return bbox2<type>(left, top, right, bottom);
    }

    template<typename type>
    static constexpr auto normalize(const line2<type>& line, const bbox2<type>& contour)
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

    // TODO need test
    template<typename type>
    static constexpr auto square_length(const line2<type>& line)
    {
        auto x_diff = line.x1 - line.x2;
        auto y_diff = line.y1 - line.y2;

        return x_diff * x_diff + y_diff * y_diff;
    }

    // TODO need test
    template<typename type>
    static constexpr auto length(const line2<type>& line)
    {
        return std::sqrt(square_length(line));
    }

    template<typename type>
    static constexpr auto to_guide_vector(const line2<type> line)
    {
        return vector2<type>(line.x2 - line.x1, line.y2 - line.y1);
    }
};

} // namespace callisto::math