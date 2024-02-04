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
    template<typename type_1, typename type_2>
    inline static constexpr auto
    square_distance(const point2<type_1>& p1, const point2<type_2>& p2) noexcept
    {
        auto dx = p1.x - p2.x;
        auto dy = p1.y - p2.y;

        return dx * dx + dy * dy;
    }

    template<typename type_1, typename type_2>
    inline static constexpr double distance(const point2<type_1>& p1, const point2<type_2>& p2) noexcept
    {
        auto square_dist = square_distance(p1, p2);

        return std::sqrt(square_dist);
    }

    template<typename type>
    inline static constexpr auto rotate(const point2<type>& point, double angle) noexcept
    {
        auto& x = point.x;
        auto& y = point.y;

        auto sin = std::sin(angle);
        auto cos = std::cos(angle);

        auto rot_x = x * cos - y * sin;
        auto rot_y = x * sin + y * cos;

        return point2d(rot_x, rot_y);
    }

    template<typename type, typename anchor_type>
    inline static constexpr auto
    rotate_anchor(const point2<type>& point, double angle, const point2<anchor_type>& anchor) noexcept
    {
        auto x = point.x - anchor.x;
        auto y = point.y - anchor.y;

        auto sin = std::sin(angle);
        auto cos = std::cos(angle);

        auto rot_x = x * cos - y * sin;
        auto rot_y = x * sin + y * cos;

        rot_x += anchor.x;
        rot_y += anchor.y;

        return point2d(rot_x, rot_y);
    }

    template<typename type, typename bbox_type>
    inline static constexpr auto clamp(const point2<type>& point, const bbox2<bbox_type>& bbox) noexcept
    {
        auto x = clamp_f(point.x, bbox.x1, bbox.x2);
        auto y = clamp_f(point.y, bbox.y1, bbox.y2);

        return point2<decltype(x)>(x, y);
    };

    template<typename type, typename bbox_type>
    inline static constexpr auto normalize(const point2<type>& point, const bbox2<bbox_type>& bbox) noexcept
    {
        auto w = bbox.width();
        auto h = bbox.height();

        auto x = (point.x - bbox.x1) / w;
        auto y = (point.y - bbox.y1) / h;

        return point2<decltype(x)>(x, y);
    }
};

} // namespace callisto::math