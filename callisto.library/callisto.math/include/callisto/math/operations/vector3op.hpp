#pragma once

// std
#include <cmath>
// project
#include <callisto/math/primitives/alg_tuple3.hpp>

namespace callisto::math
{

struct vector3op
{
    template<typename type>
    static constexpr auto square_of_length(const vector3<type>& vector) noexcept
    {
        auto& x = vector.x;
        auto& y = vector.y;
        auto& z = vector.z;

        return x * x + y * y + z * z;
    }

    template<typename type>
    static constexpr auto length(const vector3<type>& vector) noexcept
    {
        auto square_len = square_of_length(vector);

        return std::sqrt(square_len);
    }

    template<typename type>
    static constexpr auto
    normalize(const vector3<type>& vector, double normalize_value = 1.0) noexcept
    {
        auto scale = normalize_value / length(vector);

        auto x = vector.x * scale;
        auto y = vector.y * scale;
        auto z = vector.z * scale;

        return vector3<decltype(x)>(x, y, z);
    }

    template<typename type>
    static constexpr auto cross_product(const vector3<type>& a, const vector3<type>& b) noexcept
    {
        auto x = a.y * b.z - b.y * a.z;
        auto y = a.z * b.x - b.z * a.x;
        auto z = a.x * b.y - b.x * a.y;

        return vector3<type>(x, y, z);
    }
};

} // namespace callisto::math