#pragma once

// project
#include <callisto/math/error.hpp>

template<typename point_type_a, typename point_type_b>
inline static constexpr bool
rel_err_point2_equal(const point_type_a& a, const point_type_b& b, double rel_acc) noexcept
{
    return c_m::relative_error(a.x, rel_acc) == b.x && c_m::relative_error(a.y, rel_acc) == b.y;
}

template<typename point_type_a, typename point_type_b>
inline static constexpr bool
abs_err_point2_equal(const point_type_a& a, const point_type_b& b, double abs_acc) noexcept
{
    return c_m::absolute_error(a.x, abs_acc) == b.x && c_m::absolute_error(a.y, abs_acc) == b.y;
}

template<typename bbox_type_a, typename bbox_type_b>
inline static constexpr bool
rel_err_bbox2_equal(const bbox_type_a& a, const bbox_type_b b, double rel_acc) noexcept
{
    // ToDo
    return c_m::relative_error(a.x1, rel_acc) == b.x1 && c_m::relative_error(a.y1, rel_acc) == b.y1
           && c_m::relative_error(a.x2, rel_acc) == b.x2
           && c_m::relative_error(a.y2, rel_acc) == b.y2;
}

template<typename bbox_type_a, typename bbox_type_b>
inline static constexpr bool
abs_err_bbox2_equal(const bbox_type_a& a, const bbox_type_b b, double abs_acc) noexcept
{
    // ToDo
    return c_m::relative_error(a.x1, abs_acc) == b.x1 && c_m::relative_error(a.y1, abs_acc) == b.y1
           && c_m::relative_error(a.x2, abs_acc) == b.x2
           && c_m::relative_error(a.y2, abs_acc) == b.y2;
}