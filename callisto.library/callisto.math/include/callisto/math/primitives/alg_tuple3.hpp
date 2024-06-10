#pragma once

// std
#include <cstdint>
#include <utility>
// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

// project

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct alg_tuple3
{
    using value_type = _value_type;

    union
    {
        value_type v1;

        value_type x;

        value_type width;

        value_type r;
    };

    union
    {
        value_type v2;

        value_type y;

        value_type height;

        value_type g;
    };

    union
    {
        value_type v3;

        value_type z;

        value_type depth;

        value_type b;
    };

    static constexpr alg_tuple3 empty() noexcept { return alg_tuple3(0, 0, 0); }

    static constexpr alg_tuple3 from_scalar(value_type val) noexcept
    {
        return alg_tuple3(val, val, val);
    }

#pragma region construct_and_destruct

    constexpr alg_tuple3() noexcept {}

    constexpr alg_tuple3(value_type v1, value_type v2, value_type v3) noexcept
    {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }

    constexpr alg_tuple3(const alg_tuple3& values) noexcept
    {
        v1 = values.v1;
        v2 = values.v2;
        v3 = values.v3;
    }

#pragma endregion

#pragma region methods

    template<callisto::framework::concept_arithmetic cast_type>
    constexpr auto as() const noexcept
    {
        return alg_tuple3<cast_type>(v1, v2, v3);
    }

#pragma endregion

#pragma region operators

    // ADDITION
    constexpr auto operator+(const alg_tuple3& other_tuple) const noexcept
    {
        return alg_tuple3(v1 + other_tuple.v1, v2 + other_tuple.v2, v3 + other_tuple.v3);
    }

    constexpr auto operator+(value_type value) const noexcept
    {
        return alg_tuple3(v1 + value, v2 + value, v3 + value);
    }

    constexpr alg_tuple3& operator+=(const alg_tuple3& other_tuple) noexcept
    {
        v1 += other_tuple.v1;
        v2 += other_tuple.v2;
        v3 += other_tuple.v3;

        return *this;
    }

    constexpr alg_tuple3& operator+=(value_type value) noexcept
    {
        v1 += value;
        v2 += value;
        v3 += value;

        return *this;
    }

    // INVERSE
    constexpr auto operator-() const noexcept { return alg_tuple3(-v1, -v2, -v3); }

    // SUBSTRACTION
    constexpr auto operator-(const alg_tuple3& other_tuple) const noexcept
    {
        return alg_tuple3(v1 - other_tuple.v1, v2 - other_tuple.v2, v3 - other_tuple.v3);
    }

    constexpr auto operator-(value_type value) const noexcept
    {
        return alg_tuple3(v1 - value, v2 - value, v3 - value);
    }

    constexpr alg_tuple3& operator-=(const alg_tuple3& other_tuple) noexcept
    {
        v1 -= other_tuple.v1;
        v2 -= other_tuple.v2;
        v3 -= other_tuple.v3;

        return *this;
    }

    constexpr alg_tuple3& operator-=(value_type value) noexcept
    {
        v1 -= value;
        v2 -= value;
        v3 -= value;

        return *this;
    }

    // MULTIPLICATION
    constexpr auto operator*(const alg_tuple3& other_tuple) const noexcept
    {
        return alg_tuple3(v1 * other_tuple.v1, v2 * other_tuple.v2, v3 * other_tuple.v3);
    }

    constexpr auto operator*(value_type value) const noexcept
    {
        return alg_tuple3(v1 * value, v2 * value, v3 * value);
    }

    constexpr alg_tuple3& operator*=(const alg_tuple3& other_tuple) noexcept
    {
        v1 *= other_tuple.v1;
        v2 *= other_tuple.v2;
        v3 *= other_tuple.v3;

        return *this;
    }

    constexpr alg_tuple3& operator*=(value_type value) noexcept
    {
        v1 *= value;
        v2 *= value;
        v3 *= value;

        return *this;
    }

    // DIVISION
    constexpr auto operator/(const alg_tuple3& other_tuple) const noexcept
    {
        return alg_tuple3(v1 / other_tuple.v1, v2 / other_tuple.v2, v3 / other_tuple.v3);
    }

    constexpr auto operator/(value_type value) const noexcept
    {
        return alg_tuple3(v1 / value, v2 / value, v3 / value);
    }

    constexpr alg_tuple3& operator/=(const alg_tuple3& other_tuple) noexcept
    {
        v1 /= other_tuple.v1;
        v2 /= other_tuple.v2;
        v3 /= other_tuple.v3;

        return *this;
    }

    constexpr alg_tuple3& operator/=(value_type value) noexcept
    {
        v1 /= value;
        v2 /= value;
        v3 /= value;

        return *this;
    }

    constexpr bool operator==(const alg_tuple3& other_tuple) const noexcept
    {
        return v1 == other_tuple.v1 && v2 == other_tuple.v2 && v3 == other_tuple.v3;
    }

    constexpr bool operator!=(const alg_tuple3& other_tuple) const noexcept
    {
        return v1 != other_tuple.v1 || v2 != other_tuple.v2 || v3 != other_tuple.v3;
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic val_type>
alg_tuple3(val_type, val_type, val_type) -> alg_tuple3<val_type>;

#pragma region alias

using alg_tuple3i = alg_tuple3<int32_t>;

using alg_tuple3l = alg_tuple3<int64_t>;

using alg_tuple3f = alg_tuple3<float>;

using alg_tuple3d = alg_tuple3<double>;

template<typename type>
using point3 = alg_tuple3<type>;

using point3i = point3<int32_t>;

using point3l = point3<int64_t>;

using point3f = point3<float>;

using point3d = point3<double>;

template<typename type>
using vector3 = alg_tuple3<type>;

using vector3i = vector3<int32_t>;

using vector3l = vector3<int64_t>;

using vector3f = vector3<float>;

using vector3d = vector3<double>;

template<typename type>
using size3 = alg_tuple3<type>;

using size3i = size3<int32_t>;

using size3l = size3<int64_t>;

using size3f = size3<float>;

using size3d = size3<double>;

template<typename type>
using color3 = alg_tuple3<type>;

using color3i = color3<int32_t>;

using color3l = color3<int64_t>;

using color3f = color3<float>;

using color3d = color3<double>;

#pragma endregion

} // namespace callisto::math