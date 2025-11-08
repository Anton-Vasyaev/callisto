#pragma once

// std
#include <cmath>
#include <span>
// project
#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/math/primitives/bbox2.hpp>
#include <callisto/framework/types/type_traits.hpp>
#include <callisto/math/functions.hpp>
// project
#include "auxiliary.hpp"

namespace callisto::math
{
struct point2op
{
    template<typename type>
    static constexpr auto square_distance(const point2<type>& p1, const point2<type>& p2) noexcept
    {
        auto dx = p1.x - p2.x;
        auto dy = p1.y - p2.y;

        return dx * dx + dy * dy;
    }

    template<typename type>
    static constexpr std::conditional_t<std::is_same_v<type, double>, double, float>
    distance(const point2<type>& p1, const point2<type>& p2) noexcept
    {
        auto square_dist = square_distance(p1, p2);

        return std::sqrt(square_dist);
    }

    template<
        typename type,
        typename calc_type = std::conditional_t<std::is_same_v<type, double>, double, float>>
    static constexpr auto rotate(const point2<type>& point, calc_type angle) noexcept
    {
        calc_type x = point.x;
        calc_type y = point.y;

        calc_type sin = std::sin(angle);
        calc_type cos = std::cos(angle);

        calc_type rot_x = x * cos - y * sin;
        calc_type rot_y = x * sin + y * cos;

        return point2<type>(rot_x, rot_y);
    }

    template<
        typename type,
        typename calc_type = std::conditional_t<std::is_same_v<type, double>, double, float>>
    static constexpr auto
    rotate_anchor(const point2<type>& point, calc_type angle, const point2<type>& anchor) noexcept
    {
        calc_type x = point.x - anchor.x;
        calc_type y = point.y - anchor.y;

        calc_type sin = std::sin(angle);
        calc_type cos = std::cos(angle);

        calc_type rot_x = x * cos - y * sin;
        calc_type rot_y = x * sin + y * cos;

        rot_x += anchor.x;
        rot_y += anchor.y;

        return point2<type>(rot_x, rot_y);
    }

    template<typename type>
    static constexpr auto clamp(const point2<type>& point, const bbox2<type>& bbox) noexcept
    {
        auto x = clamp_f(point.x, bbox.x1, bbox.x2);
        auto y = clamp_f(point.y, bbox.y1, bbox.y2);

        return point2<type>(x, y);
    };

    template<typename type>
    static constexpr auto normalize(const point2<type>& point, const bbox2<type>& bbox) noexcept
    {
        auto w = bbox.width();
        auto h = bbox.height();

        auto x = (point.x - bbox.x1) / w;
        auto y = (point.y - bbox.y1) / h;

        return point2<type>(x, y);
    }

    template<typename type>
    static constexpr auto
    reverse_normalize(const point2<type>& point, const bbox2<type>& bbox) noexcept
    {
        auto contour_w = bbox.width();
        auto contour_h = bbox.height();

        auto x = point.x * contour_w + bbox.x1;
        auto y = point.y * contour_h + bbox.y1;

        return point2<type>(x, y);
    }

    template<typename type>
    static constexpr bbox2<type> get_box_contour(std::span<point2<type>> points)
    {
        type min_x = points[0].x;
        type max_x = points[0].x;

        type min_y = points[0].y;
        type max_y = points[0].y;

        for (auto& p : points)
        {
            min_x = min_f(min_x, p.x);
            max_x = max_f(max_x, p.x);

            min_y = min_f(min_y, p.y);
            max_y = max_f(max_y, p.y);
        }

        return bbox2<type>(min_x, min_y, max_x, max_y);
    }
};

} // namespace callisto::math