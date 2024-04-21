#pragma once

#include <callisto/math/primitives/alg_tuple3.hpp>

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct line3
{
    using value_type = _value_type;

    using point_type = point3<value_type>;

    value_type x1;
    value_type y1;
    value_type z1;

    value_type x2;
    value_type y2;
    value_type z2;

    inline static constexpr line3 empty() noexcept { return line3(0, 0, 0, 0, 0, 0); }

#pragma region construct_and_destruct

    inline constexpr line3() {}

    inline constexpr line3(
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

    inline constexpr line3(const point3<value_type>& start, const point3<value_type>& end) noexcept
    {
        x1 = start.x;
        y1 = start.y;
        z1 = start.z;

        x2 = end.x;
        y2 = end.y;
        z2 = end.z;
    }

    inline constexpr line3(const line3<value_type>& other_line) noexcept
    {
        x1 = other_line.x1;
        y1 = other_line.y1;
        z1 = other_line.z1;

        x2 = other_line.x2;
        y2 = other_line.y2;
        z2 = other_line.z2;
    }

#pragma endregion

#pragma region methods

    template<callisto::framework::concept_arithmetic cast_type>
    inline constexpr auto as() const noexcept
    {
        return line3<cast_type>(x1, y1, z1, x2, y2, z2);
    }

    inline constexpr auto first() const noexcept { return point3<value_type>(x1, y1, z1); }

    inline constexpr auto second() const noexcept { return point3<value_type>(x2, y2, z2); }

    inline constexpr auto center() const noexcept
    {
        auto x_c = (x1 + x2) / 2;
        auto y_c = (y1 + y2) / 2;
        auto z_c = (z1 + z2) / 2;

        return point3<value_type>(x_c, y_c, z_c);
    }

    inline constexpr void set_first(const point3<value_type>& point) noexcept
    {
        x1 = point.x;
        y1 = point.y;
        z1 = point.z;
    }

    inline constexpr void set_second(const point3<value_type>& point) noexcept
    {
        x2 = point.x;
        y2 = point.y;
        z2 = point.z;
    }

#pragma endregion

#pragma region operators

    inline constexpr bool operator==(const line3& other_line) const noexcept
    {
        return this->x1 == other_line.x1 && this->x2 == other_line.x2 && this->y1 == other_line.y1
               && this->y2 == other_line.y2 && this->z1 == other_line.z1
               && this->z2 == other_line.z2;
    }

    inline constexpr bool operator!=(const line3& other_line) const noexcept
    {
        return this->x1 != other_line.x1 || this->x2 != other_line.x2 || this->y1 != other_line.y1
               || this->y2 != other_line.y2 || this->z1 != other_line.z1
               || this->z2 != other_line.z2;
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic val_type>
line3(val_type, val_type, val_type, val_type, val_type, val_type) -> line3<val_type>;

template<typename point_type>
line3(point_type, point_type) -> line3<typename point_type::value_type>;

using line3i = line3<int32_t>;
using line3l = line3<int64_t>;
using line3f = line3<float>;
using line3d = line3<double>;

} // namespace callisto::math