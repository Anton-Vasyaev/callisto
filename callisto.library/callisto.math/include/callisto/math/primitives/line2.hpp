#pragma once

// project
#include "alg_tuple2.hpp"

namespace callisto::math
{

// imports
namespace
{
namespace c_f = callisto::framework;
}

template<c_f::concept_fundamental _value_type>
struct line2
{
    using value_type = _value_type;

    using point_type = point2<value_type>;

    value_type x1;
    value_type y1;
    value_type x2;
    value_type y2;

    inline static constexpr line2 empty() noexcept { return line2(0, 0, 0, 0); }

#pragma region construct_and_destruct

    inline constexpr line2() {}

    template<
        c_f::concept_fundamental type_x1,
        c_f::concept_fundamental type_y1,
        c_f::concept_fundamental type_x2,
        c_f::concept_fundamental type_y2>
    inline constexpr line2(type_x1 x1, type_y1 y1, type_x2 x2, type_y2 y2) noexcept
    {
        this->x1 = x1;
        this->y1 = y1;

        this->x2 = x2;
        this->y2 = y2;
    }

    template<c_f::concept_fundamental start_type, c_f::concept_fundamental end_type>
    inline constexpr line2(const point2<start_type>& start, const point2<end_type>& end) noexcept
    {
        x1 = start.x;
        y1 = start.y;

        x2 = end.x;
        y2 = end.y;
    }

    template<c_f::concept_fundamental other_type>
    inline constexpr line2(const line2<other_type>& other_line) noexcept
    {
        x1 = other_line.x1;
        y1 = other_line.y1;

        x2 = other_line.x2;
        y2 = other_line.y2;
    }

#pragma endregion

#pragma region methods

    inline constexpr auto first() const noexcept { return point2<value_type>(x1, y1); }

    inline constexpr auto second() const noexcept { return point2<value_type>(x2, y2); }

    inline constexpr auto center() const noexcept
    {
        auto x_c = (x1 + x2) / 2.0;
        auto y_c = (y1 + y2) / 2.0;

        return point2<value_type>(x_c, y_c);
    }

    template<c_f::concept_fundamental type>
    inline constexpr void set_first(const point2<type>& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
    }

    template<c_f::concept_fundamental type>
    inline constexpr void set_second(const point2<type>& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
    }

#pragma endregion

#pragma region operators

    template<c_f::concept_fundamental other_type>
    inline constexpr bool operator==(const line2<other_type>& other_line) const noexcept
    {
        return this->x1 == other_line.x1 && this->x2 == other_line.x2 && this->y1 == other_line.y1
               && this->y2 == other_line.y2;
    }

    template<c_f::concept_fundamental other_type>
    inline constexpr bool operator!=(const line2<other_type>& other_line) const noexcept
    {
        return this->x1 == other_line.x1 || this->x2 == other_line.x2 || this->y1 == other_line.y1
               || this->y2 == other_line.y2;
    }

#pragma endregion
};

template<
    c_f::concept_fundamental type_x1,
    c_f::concept_fundamental type_y1,
    c_f::concept_fundamental type_x2,
    c_f::concept_fundamental type_y2>
line2(type_x1, type_y1, type_x2, type_y2)
    -> line2<c_f::senior_conversion_t<type_x1, type_y1, type_x2, type_y2>>;

template<typename start_type, typename end_type>
line2(start_type, end_type) -> line2<
    c_f::senior_conversion_t<typename start_type::value_type, typename end_type::value_type>>;

using line2i = line2<int32_t>;

using line2l = line2<int64_t>;

using line2f = line2<float>;

using line2d = line2<double>;

} // namespace callisto::math