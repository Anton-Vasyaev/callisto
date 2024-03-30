#pragma once

#include <callisto/math/primitives/alg_tuple3.hpp>

namespace callisto::math
{

// imports
namespace
{
namespace c_f = callisto::framework;
}

template<typename _value_type>
struct line3
{
    using value_type = _value_type;

    using point_type = point2<value_type>;

    value_type x1;
    value_type y1;
    value_type z1;

    value_type x2;
    value_type y2;
    value_type z2;

    inline static constexpr line3 empty() noexcept { return line3(0, 0, 0, 0, 0, 0); }

#pragma region construct_and_destruct

    inline constexpr line3() {}

    template<
        typename type_x1,
        typename type_y1,
        typename type_z1,
        typename type_x2,
        typename type_y2,
        typename type_z2>
    inline constexpr line3(
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

    template<typename start_type, typename end_type>
    inline constexpr line3(const start_type& start, const end_type& end) noexcept
    {
        x1 = start.x;
        y1 = start.y;
        z1 = start.z;

        x2 = end.x;
        y2 = end.y;
        z2 = end.z;
    }

    template<typename other_line2_can_type>
    inline constexpr line3(const other_line2_can_type& other_line) noexcept
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

    inline constexpr auto first() const noexcept { return point3<value_type>(x1, y1, z1); }

    inline constexpr auto second() const noexcept { return point3<value_type>(x2, y2, z2); }

    inline constexpr auto center() const noexcept
    {
        auto x_c = (x1 + x2) / 2.0;
        auto y_c = (y1 + y2) / 2.0;
        auto z_c = (z1 + z2) / 2.0;

        return point3<value_type>(x_c, y_c, z_c);
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

#pragma endregion

#pragma region operators

    template<typename other_type>
    inline constexpr bool operator==(const line3<other_type>& other_line) const noexcept
    {
        return this->x1 == other_line.x1 && this->x2 == other_line.x2 && this->y1 == other_line.y1
               && this->y2 == other_line.y2 && this->z1 == other_line.z1
               && this->z2 == other_line.z2;
    }

    template<typename other_type>
    inline constexpr bool operator!=(const line3<other_type>& other_line) const noexcept
    {
        return this->x1 == other_line.x1 || this->x2 == other_line.x2 || this->y1 == other_line.y1
               || this->y2 == other_line.y2 || this->z1 == other_line.z1
               || this->z2 == other_line.z2;
    }

#pragma endregion
};

template<
    typename type_x1,
    typename type_y1,
    typename type_z1,
    typename type_x2,
    typename type_y2,
    typename type_z2>
line3(type_x1, type_y1, type_z1, type_x2, type_y2, type_z2)
    -> line3<c_f::senior_conversion_t<type_x1, type_y1, type_z1, type_x2, type_y2, type_z2>>;

template<typename start_type, typename end_type>
line3(start_type, end_type) -> line3<
    c_f::senior_conversion_t<typename start_type::value_type, typename end_type::value_type>>;

using line3i = line3<int32_t>;
using line3l = line3<int64_t>;
using line3f = line3<float>;
using line3d = line3<double>;

} // namespace callisto::math