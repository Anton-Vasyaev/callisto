#pragma once

// std
#include <cstdint>
#include <utility>
// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct alg_tuple2
{
    using value_type = _value_type;

    union
    {
        value_type v1;
        value_type x;
        value_type width;
    };

    union
    {
        value_type v2;
        value_type y;
        value_type height;
    };

    static constexpr alg_tuple2 empty() noexcept { return alg_tuple2(0, 0); }

    static constexpr alg_tuple2 from_scalar(value_type val) { return alg_tuple2(val, val); }

#pragma region construct_and_destruct

    constexpr alg_tuple2() noexcept {}

    constexpr alg_tuple2(value_type v1, value_type v2) noexcept
    {
        this->v1 = v1;
        this->v2 = v2;
    }

    constexpr alg_tuple2(const alg_tuple2& values) noexcept
    {
        v1 = values.v1;
        v2 = values.v2;
    }

#pragma endregion

#pragma region methods

    template<callisto::framework::concept_arithmetic cast_type>
    constexpr auto as() const noexcept
    {
        return alg_tuple2<cast_type>(v1, v2);
    }

#pragma endregion

#pragma region operators

    constexpr alg_tuple2& operator=(const alg_tuple2& other_tuple) noexcept
    {
        v1 = other_tuple.v1;
        v2 = other_tuple.v2;

        return *this;
    }

    // ADDITION
    constexpr auto operator+(const alg_tuple2& other_tuple) const noexcept
    {
        return alg_tuple2(v1 + other_tuple.v1, v2 + other_tuple.v2);
    }

    constexpr auto operator+(value_type value) const noexcept
    {
        return alg_tuple2(v1 + value, v2 + value);
    }

    constexpr alg_tuple2& operator+=(const alg_tuple2& other_tuple) noexcept
    {
        v1 += other_tuple.v1;
        v2 += other_tuple.v2;

        return *this;
    }

    constexpr alg_tuple2& operator+=(value_type value) noexcept
    {
        v1 += value;
        v2 += value;

        return *this;
    }

    // INVERSE
    constexpr auto operator-() const noexcept { return alg_tuple2(-v1, -v2); }

    // SUBSTRACTION
    constexpr auto operator-(const alg_tuple2& other_tuple) const noexcept
    {
        return alg_tuple2(v1 - other_tuple.v1, v2 - other_tuple.v2);
    }

    constexpr auto operator-(value_type value) const noexcept
    {
        return alg_tuple2(v1 - value, v2 - value);
    }

    constexpr alg_tuple2& operator-=(const alg_tuple2& other_tuple) noexcept
    {
        v1 -= other_tuple.v1;
        v2 -= other_tuple.v2;

        return *this;
    }

    constexpr alg_tuple2& operator-=(value_type value) noexcept
    {
        v1 -= value;
        v2 -= value;

        return *this;
    }

    // MULTIPLICATION
    constexpr auto operator*(const alg_tuple2& other_tuple) const noexcept
    {
        return alg_tuple2(v1 * other_tuple.v1, v2 * other_tuple.v2);
    }

    constexpr auto operator*(value_type value) const noexcept
    {
        return alg_tuple2(v1 * value, v2 * value);
    }

    constexpr alg_tuple2& operator*=(const alg_tuple2& other_tuple) noexcept
    {
        v1 *= other_tuple.v1;
        v2 *= other_tuple.v2;

        return *this;
    }

    constexpr alg_tuple2& operator*=(value_type value) noexcept
    {
        v1 *= value;
        v2 *= value;

        return *this;
    }

    // DIVISION
    constexpr auto operator/(const alg_tuple2& other_tuple) const noexcept
    {
        return alg_tuple2(v1 / other_tuple.v1, v2 / other_tuple.v2);
    }

    constexpr auto operator/(value_type value) const noexcept
    {
        return alg_tuple2(v1 / value, v2 / value);
    }

    constexpr const alg_tuple2& operator/=(const alg_tuple2& other_tuple) noexcept
    {
        v1 /= other_tuple.v1;
        v2 /= other_tuple.v2;

        return *this;
    }

    constexpr const alg_tuple2& operator/=(value_type value) noexcept
    {
        v1 /= value;
        v2 /= value;

        return *this;
    }

    constexpr bool operator==(const alg_tuple2& other_tuple) const noexcept
    {
        return v1 == other_tuple.v1 && v2 == other_tuple.v2;
    }

    constexpr bool operator!=(const alg_tuple2& other_tuple) const noexcept
    {
        return v1 != other_tuple.v1 || v2 != other_tuple.v2;
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic val_type>
alg_tuple2(val_type, val_type) -> alg_tuple2<val_type>;

#pragma region alias

using alg_tuple2i = alg_tuple2<int32_t>;

using alg_tuple2l = alg_tuple2<int64_t>;

using alg_tuple2f = alg_tuple2<float>;

using alg_tuple2d = alg_tuple2<double>;

template<typename type>
using point2 = alg_tuple2<type>;

using point2i = point2<int32_t>;

using point2l = point2<int64_t>;

using point2f = point2<float>;

using point2d = point2<double>;

template<typename type>
using vector2 = alg_tuple2<type>;

using vector2i = vector2<int32_t>;

using vector2l = vector2<int64_t>;

using vector2f = vector2<float>;

using vector2d = vector2<double>;

template<typename type>
using size2 = alg_tuple2<type>;

using size2i = size2<int32_t>;

using size2l = size2<int64_t>;

using size2f = size2<float>;

using size2d = size2<double>;

#pragma endregion

} // namespace callisto::math