#pragma once

// project
#include <callisto/math/primitives.hpp>
#include <callisto/math/error.hpp>

template<typename type>
constexpr bool rel_err_point2_equal(
    const callisto::math::point2<type>& a,
    const callisto::math::point2<type>& b,
    type                                rel_acc
) noexcept
{
    return c_m::relative_error(a.x, rel_acc) == b.x && c_m::relative_error(a.y, rel_acc) == b.y;
}

template<typename type>
constexpr bool abs_err_point2_equal(
    const callisto::math::point2<type>& a,
    const callisto::math::point2<type>& b,
    type                                abs_acc
) noexcept
{
    return c_m::absolute_error(a.x, abs_acc) == b.x && c_m::absolute_error(a.y, abs_acc) == b.y;
}

// FUTURE
template<typename type>
constexpr bool rel_err_point3_equal(
    const callisto::math::point3<type>& a,
    const callisto::math::point3<type>& b,
    type                                rel_acc
) noexcept
{
    return c_m::relative_error(a.x, rel_acc) == b.x && c_m::relative_error(a.y, rel_acc) == b.y
           && c_m::relative_error(a.z, rel_acc) == b.z;
}

template<typename type>
constexpr bool abs_err_point3_equal(
    const callisto::math::point3<type>& a,
    const callisto::math::point3<type>& b,
    type                                abs_acc
) noexcept
{
    return c_m::absolute_error(a.x, abs_acc) == b.x && c_m::absolute_error(a.y, abs_acc) == b.y
           && c_m::absolute_error(a.z, abs_acc) == b.z;
}

template<typename type>
constexpr bool rel_err_bbox2_equal(
    const callisto::math::bbox2<type>& a,
    const callisto::math::bbox2<type>& b,
    type                               rel_acc
) noexcept
{
    return c_m::relative_error(a.x1, rel_acc) == b.x1 && c_m::relative_error(a.y1, rel_acc) == b.y1
           && c_m::relative_error(a.x2, rel_acc) == b.x2
           && c_m::relative_error(a.y2, rel_acc) == b.y2;
}

template<typename type>
constexpr bool abs_err_bbox2_equal(
    const callisto::math::bbox2<type>& a,
    const callisto::math::bbox2<type>& b,
    type                               abs_acc
) noexcept
{
    return c_m::absolute_error(a.x1, abs_acc) == b.x1 && c_m::absolute_error(a.y1, abs_acc) == b.y1
           && c_m::absolute_error(a.x2, abs_acc) == b.x2
           && c_m::absolute_error(a.y2, abs_acc) == b.y2;
}

// FUTURE
template<typename type>
constexpr bool rel_err_bbox3_equal(
    const callisto::math::bbox3<type>& a,
    const callisto::math::bbox3<type>& b,
    type                               rel_acc
) noexcept
{
    return c_m::relative_error(a.x1, rel_acc) == b.x1 && c_m::relative_error(a.y1, rel_acc) == b.y1
           && c_m::relative_error(a.z1, rel_acc) == b.z1
           && c_m::relative_error(a.x2, rel_acc) == b.x2
           && c_m::relative_error(a.y2, rel_acc) == b.y2
           && c_m::relative_error(a.z2, rel_acc) == b.z2;
}

// FUTURE
template<typename type>
constexpr bool abs_err_bbox3_equal(
    const callisto::math::bbox2<type>& a,
    const callisto::math::bbox2<type>& b,
    type                               abs_acc
) noexcept
{
    return c_m::absolute_error(a.x1, abs_acc) == b.x1 && c_m::absolute_error(a.y1, abs_acc) == b.y1
           && c_m::absolute_error(a.z1, abs_acc) == b.z1
           && c_m::absolute_error(a.x2, abs_acc) == b.x2
           && c_m::absolute_error(a.y2, abs_acc) == b.y2
           && c_m::absolute_error(a.z2, abs_acc) == b.z2;
}

template<typename type>
constexpr bool rel_err_line2_equal(
    const callisto::math::line2<type>& a,
    const callisto::math::line2<type>& b,
    type                               rel_acc
) noexcept
{
    return (c_m::relative_error(a.x1, rel_acc) == b.x1 && c_m::relative_error(a.y1, rel_acc) == b.y1
            && c_m::relative_error(a.x2, rel_acc) == b.x2
            && c_m::relative_error(a.y2, rel_acc) == b.y2)
           || (c_m::relative_error(a.x1, rel_acc) == b.x2
               && c_m::relative_error(a.y1, rel_acc) == b.y2
               && c_m::relative_error(a.x2, rel_acc) == b.x1
               && c_m::relative_error(a.y2, rel_acc) == b.y1);
}

template<typename type>
constexpr bool abs_err_line2_equal(
    const callisto::math::line2<type>& a,
    const callisto::math::line2<type>& b,
    type                               abs_acc
) noexcept
{
    return (c_m::absolute_error(a.x1, abs_acc) == b.x1 && c_m::absolute_error(a.y1, abs_acc) == b.y1
            && c_m::absolute_error(a.x2, abs_acc) == b.x2
            && c_m::absolute_error(a.y2, abs_acc) == b.y2)
           || (c_m::absolute_error(a.x1, abs_acc) == b.x2
               && c_m::absolute_error(a.y1, abs_acc) == b.y2
               && c_m::absolute_error(a.x2, abs_acc) == b.x1
               && c_m::absolute_error(a.y2, abs_acc) == b.y1);
}