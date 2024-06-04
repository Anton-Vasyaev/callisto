#pragma once

// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>
#include "alg_tuple3.hpp"

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct bbox3
{
    using value_type = _value_type;

    value_type x1;
    value_type y1;
    value_type z1;

    value_type x2;
    value_type y2;
    value_type z2;

    static constexpr bbox3 empty() noexcept { return bbox3(0, 0, 0, 0, 0, 0); }

#pragma region construct_and_destruct

    constexpr bbox3() noexcept = default;

    constexpr bbox3(
        value_type x1,
        value_type y1,
        value_type z1,
        value_type x2,
        value_type y2,
        value_type z2
    ) noexcept
    {
        this->x1 = x1;
        this->y1 = y1;
        this->z1 = z1;

        this->x2 = x2;
        this->y2 = y2;
        this->z2 = z2;
    }

    constexpr bbox3(const point3<value_type>& p1, const point3<value_type>& p2)
    {
        x1 = p1.x;
        y1 = p1.y;
        z1 = p1.z;

        x2 = p2.x;
        y2 = p2.y;
        z2 = p2.z;
    }

    constexpr bbox3(const bbox3& other_bbox) noexcept
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

    template<callisto::framework::concept_arithmetic cast_type>
    constexpr auto as() const noexcept
    {
        return bbox3<cast_type>(x1, y1, z1, x2, y2, z2);
    }

    constexpr auto left_top_near() const noexcept { return point3<value_type>(x1, y1, z1); }

    constexpr auto left_bottom_near() const noexcept { return point3<value_type>(x1, y2, z1); }

    constexpr auto right_bottom_near() const noexcept { return point3<value_type>(x2, y2, z1); }

    constexpr auto right_top_near() const noexcept { return point3<value_type>(x2, y1, z1); }

    constexpr auto left_top_far() const noexcept { return point3<value_type>(x1, y1, z2); }

    constexpr auto left_bottom_far() const noexcept { return point3<value_type>(x1, y2, z2); }

    constexpr auto right_bottom_far() const noexcept { return point3<value_type>(x2, y2, z2); }

    constexpr auto right_top_far() const noexcept { return point3<value_type>(x2, y1, z2); }

    constexpr value_type width() const noexcept { return x2 - x1; }

    constexpr value_type height() const noexcept { return y2 - y1; }

    constexpr value_type depth() const noexcept { return z2 - z1; }

    constexpr value_type volume() const noexcept { return width() * height() * depth(); }

    constexpr size3<value_type> size() const noexcept
    {
        return size3<value_type>(width(), height(), depth());
    }

    constexpr void set_first(const point3<value_type>& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
        z1 = point.z;
    }

    constexpr void set_second(const point3<value_type>& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
        z2 = point.z;
    }

#pragma region operators

    constexpr bool operator==(const bbox3& other) const noexcept
    {
        return (x1 == other.x1 && y1 == other.y1 && z1 == other.z1)
               && (x2 == other.x2 && y2 == other.y2 && z2 == other.z2);
    }

    constexpr bool operator!=(const bbox3& other) const noexcept
    {
        return (x1 != other.x1 || y1 != other.y1 || z1 != other.z1)
               || (x2 != other.x2 || y2 != other.y2 || z2 != other.z2);
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic val_type>
bbox3(val_type, val_type, val_type, val_type, val_type, val_type) -> bbox3<val_type>;

template<typename point_type>
bbox3(point_type, point_type) -> bbox3<typename point_type::value_type>;

#pragma region alias

using bbox3i = bbox3<int32_t>;
using bbox3l = bbox3<int64_t>;
using bbox3f = bbox3<float>;
using bbox3d = bbox3<double>;

#pragma endregion

} // namespace callisto::math