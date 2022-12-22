#pragma once

// std
#include <cmath>
// project
#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/framework/types/type_traits.hpp>
#include <callisto/math/functions.hpp>
// project
#include "auxiliary.hpp"

namespace callisto::math
{

namespace
{
template<typename... args_type>
auto _clamp_f(args_type&&... args) -> decltype(clamp(std::forward<args_type>(args)...))
{
    return clamp(std::forward<args_type>(args)...);
}
} // namespace

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

    template<
        typename _calc_type  = void,
        typename point1_type = alg_tuple2i,
        typename point2_type = alg_tuple2i>
    inline static constexpr auto distance(const point1_type& p1, const point2_type& p2) noexcept
    {
        using calc_type = calc_type_selection_t<
            _calc_type,
            c_f::senior_conversion_t<point1_type::value_type, point2_type::value_type>>;

        calc_type square_distance = square_distance(p1, p2);

        return std::sqrt(calc_type);
    }

    template<typename point_type, typename anchor_type = alg_tuple2i>
    inline static constexpr auto rotate(
        const point_type&  point,
        double             angle,
        const anchor_type& anchor = anchor_type::empty()
    ) noexcept
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
        auto x = _clamp_f(point.x, bbox.x1, bbox.x2);
        auto y = _clamp_f(point.y, bbox.y1, bbox.y2);

        return point2(x, y);
    };
};

} // namespace callisto::math