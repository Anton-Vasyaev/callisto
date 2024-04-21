#pragma once

// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>
#include "alg_tuple2.hpp"

namespace callisto::math
{
namespace
{
namespace c_f = callisto::framework;
}

template<callisto::framework::concept_arithmetic _value_type>
struct bbox2
{
    using value_type = _value_type;

    value_type x1;
    value_type y1;
    value_type x2;
    value_type y2;

    inline static constexpr bbox2 empty() noexcept { return bbox2(0, 0, 0, 0); }

#pragma region construct_and_destruct

    inline constexpr bbox2(value_type x1, value_type y1, value_type x2, value_type y2) noexcept
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    inline constexpr bbox2(
        const point2<value_type>& left_top,
        const point2<value_type>& right_bottom
    ) noexcept
    {
        x1 = left_top.x;
        y1 = left_top.y;

        x2 = right_bottom.x;
        y2 = right_bottom.y;
    }

    inline constexpr bbox2(const bbox2& other_bbox) noexcept
    {
        x1 = other_bbox.x1;
        y1 = other_bbox.y1;
        x2 = other_bbox.x2;
        y2 = other_bbox.y2;
    }

#pragma endregion

#pragma region methods

    template<callisto::framework::concept_arithmetic cast_type>
    inline constexpr auto as() const noexcept
    {
        return bbox2<cast_type>(x1, y1, x2, y2);
    }

    inline constexpr auto left_top() const noexcept { return point2<value_type>(x1, y1); }

    inline constexpr auto left_bottom() const noexcept { return point2<value_type>(x1, y2); }

    inline constexpr auto right_bottom() const noexcept { return point2<value_type>(x2, y2); }

    inline constexpr auto right_top() const noexcept { return point2<value_type>(x2, y1); }

    inline constexpr value_type width() const noexcept { return x2 - x1; }

    inline constexpr value_type height() const noexcept { return y2 - y1; }

    inline constexpr value_type area() const noexcept { return width() * height(); }

    inline constexpr size2<value_type> size() const noexcept
    {
        return size2<value_type>(width(), height());
    }

    inline constexpr void set_first(const point2<value_type>& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
    }

    inline constexpr void set_second(const point2<value_type>& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
    }

#pragma region operators

    inline constexpr const bool operator==(const bbox2& other) const noexcept
    {
        return x1 == other.x1 && y1 == other.y1 && x2 == other.x2 && y2 == other.y2;
    }

    inline constexpr const bool operator!=(const bbox2& other) const noexcept
    {
        return x1 != other.x1 || y1 != other.y1 || x2 != other.x2 || y2 != other.y2;
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic val_type>
bbox2(val_type, val_type, val_type, val_type) -> bbox2<val_type>;

template<typename point_type>
bbox2(point_type, point_type) -> bbox2<typename point_type::value_type>;

#pragma region alias

using bbox2i = bbox2<int32_t>;
using bbox2l = bbox2<int64_t>;
using bbox2f = bbox2<float>;
using bbox2d = bbox2<double>;

#pragma endregion

} // namespace callisto::math