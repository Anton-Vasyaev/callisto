#pragma once

// 3rd party
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>
#include <callisto/math/primitives/alg_tuple3.hpp>

namespace callisto::math
{
namespace
{
namespace c_f = callisto::framework;
}

template<c_f::concept_fundamental _value_type>
struct bbox3
{
    using value_type = _value_type;

    value_type x1;
    value_type y1;
    value_type z1;

    value_type x2;
    value_type y2;
    value_type z2;

    inline static constexpr bbox3 empty() noexcept { return bbox3(0, 0, 0, 0, 0, 0); }

#pragma region construct_and_destruct

    template<
        c_f::concept_fundamental type_x1,
        c_f::concept_fundamental type_y1,
        c_f::concept_fundamental type_z1,
        c_f::concept_fundamental type_x2,
        c_f::concept_fundamental type_y2,
        c_f::concept_fundamental type_z2>
    inline constexpr bbox3(
        type_x1 x1,
        type_y1 y1,
        type_z1 z1,
        type_x2 x2,
        type_y2 y2,
        type_z2 z2
    ) noexcept
    {
        this->x1 = x1;
        this->y1 = y1;
        this->z1 = z1;

        this->x2 = x2;
        this->y2 = y2;
        this->z2 = z2;
    }

    template<typename other_bbox_type>
    inline constexpr bbox3(const other_bbox_type& other_bbox) noexcept
    {
        x1 = other_bbox.x1;
        y1 = other_bbox.y1;
        z1 = other_bbox.z1;

        x2 = other_bbox.x2;
        y2 = other_bbox.y2;
        z2 = other_bbox.z2;
    }

#pragma endregion

#pragma region methods

    template<c_f::concept_fundamental cast_type>
    inline constexpr auto as() const noexcept
    {
        return bbox2<cast_type>(x1, y1, z1, x2, y2, z2);
    }

    inline constexpr auto left_top_far() const noexcept { return point3(x1, y1, z1); }

    inline constexpr auto left_bottom_far() const noexcept { return point3(x1, y2, z1); }

    inline constexpr auto right_bottom_far() const noexcept { return point3(x2, y2, z1); }

    inline constexpr auto right_top_far() const noexcept { return point3(x2, y1, z1); }

    inline constexpr auto left_top_near() const noexcept { return point3(x1, y1, z2); }

    inline constexpr auto left_bottom_near() const noexcept { return point3(x1, y2, z2); }

    inline constexpr auto right_bottom_near() const noexcept { return point3(x2, y2, z2); }

    inline constexpr auto right_top_near() const noexcept { return point3(x2, y1, z2); }

    inline constexpr value_type width() const noexcept { return x2 - x1; }

    inline constexpr value_type height() const noexcept { return y2 - y1; }

    inline constexpr value_type depth() const noexcept { return z2 - z1; }

    inline constexpr value_type volume() const noexcept { return width() * height() * depth(); }

    inline constexpr size3<value_type> size() const noexcept
    {
        return size3<value_type>(width(), height(), depth());
    }

    template<typename point_type>
    inline constexpr void set_first(const point_type& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
        z1 = point.z;
    }

    template<typename point_type>
    inline constexpr void set_second(const point_type& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
        z2 = point.z;
    }

#pragma region operators

    template<typename other_bbox_type>
    inline constexpr const bbox3& operator=(const other_bbox_type& other_bbox)
    {
        x1 = other_bbox.x1;
        y1 = other_bbox.y1;
        z1 = other_bbox.z1;

        x2 = other_bbox.x2;
        y2 = other_bbox.y2;
        z2 = other_bbox.z2;
    }

#pragma endregion
};

template<
    c_f::concept_fundamental type_x1,
    c_f::concept_fundamental type_y1,
    c_f::concept_fundamental type_z1,
    c_f::concept_fundamental type_x2,
    c_f::concept_fundamental type_y2,
    c_f::concept_fundamental type_z2>
bbox3(type_x1, type_y1, type_z1, type_x2, type_y2, type_z2)
    -> bbox3<c_f::senior_conversion_t<type_x1, type_y1, type_z1, type_x2, type_y2, type_z2>>;

#pragma region alias

using bbox3i = bbox3<int32_t>;
using bbox3l = bbox3<int64_t>;
using bbox3f = bbox3<float>;
using bbox3d = bbox3<double>;

#pragma endregion

} // namespace callisto::math