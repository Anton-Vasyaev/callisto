#pragma once

// std
#include <cmath>
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
    template<typename point1_type, typename point2_type>
    inline static constexpr auto
    square_distance(const point1_type& p1, const point2_type& p2) noexcept
    {
        auto dx = p1.x - p2.x;
        auto dy = p1.y - p2.y;

        return dx * dx + dy * dy;
    }

    template<typename point1_type = alg_tuple2i, typename point2_type = alg_tuple2i>
    inline static constexpr double distance(const point1_type& p1, const point2_type& p2) noexcept
    {
        auto square_dist = square_distance(p1, p2);

        return std::sqrt(square_dist);
    }

    template<typename point_type>
    inline static constexpr auto rotate(const point_type& point, double angle) noexcept
    {
        auto& x = point.x;
        auto& y = point.y;

        auto sin = std::sin(angle);
        auto cos = std::cos(angle);

        auto rot_x = x * cos - y * sin;
        auto rot_y = x * sin + y * cos;

        return point_type(rot_x, rot_y);
    }

    template<typename point_type, typename anchor_type = alg_tuple2i>
    inline static constexpr auto
    rotate_anchor(const point_type& point, double angle, const anchor_type& anchor) noexcept
    {
        auto x = point.x - anchor.x;
        auto y = point.y - anchor.y;

        auto sin = std::sin(angle);
        auto cos = std::cos(angle);

        auto rot_x = x * cos - y * sin;
        auto rot_y = x * sin + y * cos;

        rot_x += anchor.x;
        rot_y += anchor.y;

        return point_type(rot_x, rot_y);
    }

    template<typename point_type, typename bbox_type>
    inline static constexpr auto clamp(const point_type& point, const bbox_type& bbox) noexcept
    {
        auto x = clamp_f(point.x, bbox.x1, bbox.x2);
        auto y = clamp_f(point.y, bbox.y1, bbox.y2);

        return point2<decltype(x)>(x, y);
    };

    template<typename point_type, typename bbox_type>
    inline static constexpr auto normalize(const point_type& point, const bbox_type& bbox) noexcept
    {
        auto w = bbox.width();
        auto h = bbox.height();

        auto x = point.x - bbox.x1;
        auto y = point.y - bbox.y1;

        x /= w;
        y /= h;

        return point2<decltype(x)>(x, y);
    }
};

} // namespace callisto::math