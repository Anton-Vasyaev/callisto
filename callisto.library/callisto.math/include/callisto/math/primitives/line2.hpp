#pragma once

// project
#include "alg_tuple2.hpp"

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct line2
{
    using value_type = _value_type;

    using point_type = point2<value_type>;

    value_type x1;
    value_type y1;
    value_type x2;
    value_type y2;

    static constexpr line2 empty() noexcept { return line2(0, 0, 0, 0); }

#pragma region construct_and_destruct

    constexpr line2() = default;

    constexpr line2(value_type x1, value_type y1, value_type x2, value_type y2) noexcept
    {
        this->x1 = x1;
        this->y1 = y1;

        this->x2 = x2;
        this->y2 = y2;
    }

    constexpr line2(const point2<value_type>& start, const point2<value_type>& end) noexcept
    {
        x1 = start.x;
        y1 = start.y;

        x2 = end.x;
        y2 = end.y;
    }

    constexpr line2(const line2& other_line) noexcept
    {
        x1 = other_line.x1;
        y1 = other_line.y1;

        x2 = other_line.x2;
        y2 = other_line.y2;
    }

#pragma endregion

#pragma region methods

    template<callisto::framework::concept_arithmetic cast_type>
    constexpr auto as() const noexcept
    {
        return line2<cast_type>(x1, y1, x2, y2);
    }

    constexpr auto first() const noexcept { return point2<value_type>(x1, y1); }

    constexpr auto second() const noexcept { return point2<value_type>(x2, y2); }

    constexpr auto center() const noexcept
    {
        auto x_c = (x1 + x2) / 2;
        auto y_c = (y1 + y2) / 2;

        return point2<value_type>(x_c, y_c);
    }

    constexpr void set_first(const point2<value_type>& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
    }

    constexpr void set_second(const point2<value_type>& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
    }

#pragma endregion

#pragma region operators

    constexpr bool operator==(const line2& other_line) const noexcept
    {
        return this->x1 == other_line.x1 && this->x2 == other_line.x2 && this->y1 == other_line.y1
               && this->y2 == other_line.y2;
    }

    constexpr bool operator!=(const line2& other_line) const noexcept
    {
        return this->x1 != other_line.x1 || this->x2 != other_line.x2 || this->y1 != other_line.y1
               || this->y2 != other_line.y2;
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic value_type>
line2(value_type, value_type, value_type, value_type) -> line2<value_type>;

template<typename point_type>
line2(point_type, point_type) -> line2<typename point_type::value_type>;

using line2i = line2<int32_t>;

using line2l = line2<int64_t>;

using line2f = line2<float>;

using line2d = line2<double>;

} // namespace callisto::math