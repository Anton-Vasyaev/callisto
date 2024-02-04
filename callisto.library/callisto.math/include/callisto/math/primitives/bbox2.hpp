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

template<c_f::concept_fundamental _value_type>
struct bbox2
{
    using value_type = _value_type;

    value_type x1;
    value_type y1;
    value_type x2;
    value_type y2;

    inline static constexpr bbox2 empty() noexcept { return bbox2(0, 0, 0, 0); }

#pragma region construct_and_destruct

    template<
        c_f::concept_fundamental type_x1,
        c_f::concept_fundamental type_y1,
        c_f::concept_fundamental type_x2,
        c_f::concept_fundamental type_y2>
    inline constexpr bbox2(type_x1 x1, type_y1 y1, type_x2 x2, type_y2 y2) noexcept
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    template<c_f::concept_fundamental lt_type, c_f::concept_fundamental rb_type>
    inline constexpr bbox2(
        const point2<lt_type>& left_top,
        const point2<rb_type>& right_bottom
    ) noexcept
    {
        x1 = left_top.x;
        y1 = left_top.y;

        x2 = right_bottom.x;
        y2 = right_bottom.y;
    }

    template<c_f::concept_fundamental other_type>
    inline constexpr bbox2(const bbox2<other_type>& other_bbox) noexcept
    {
        x1 = other_bbox.x1;
        y1 = other_bbox.y1;
        x2 = other_bbox.x2;
        y2 = other_bbox.y2;
    }

#pragma endregion

#pragma region methods

    template<c_f::concept_fundamental cast_type>
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

    template<c_f::concept_fundamental type>
    inline constexpr void set_left_top(const point2<type>& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
    }

    template<c_f::concept_fundamental type>
    inline constexpr void set_right_bottom(const point2<type>& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
    }

#pragma region operators

    template<c_f::concept_fundamental other_type>
    inline constexpr const bbox2& operator=(const bbox2<other_type>& other_bbox) noexcept
    {
        x1 = other_bbox.x1;
        y1 = other_bbox.y1;

        x2 = other_bbox.x2;
        y2 = other_bbox.y2;
    }

#pragma endregion
};

template<
    c_f::concept_fundamental type_x1,
    c_f::concept_fundamental type_y1,
    c_f::concept_fundamental type_x2,
    c_f::concept_fundamental type_y2>
bbox2(type_x1, type_y1, type_x2, type_y2)
    -> bbox2<c_f::senior_conversion_t<type_x1, type_y1, type_x2, type_y2>>;

template<typename left_top_type, typename right_bottom_type>
bbox2(left_top_type, right_bottom_type) -> bbox2<c_f::senior_conversion_t<
    typename left_top_type::value_type,
    typename right_bottom_type::value_type>>;

#pragma region alias

using bbox2i = bbox2<int32_t>;
using bbox2l = bbox2<int64_t>;
using bbox2f = bbox2<float>;
using bbox2d = bbox2<double>;

#pragma endregion

} // namespace callisto::math