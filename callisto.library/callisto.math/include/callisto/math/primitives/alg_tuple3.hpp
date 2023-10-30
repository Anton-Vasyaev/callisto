#pragma once

// std
#include <cstdint>
#include <utility>
// 3rd party
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

// project

namespace callisto::math
{

namespace
{
namespace c_f = callisto::framework;
}

template<c_f::concept_fundamental _value_type>
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

    inline static constexpr alg_tuple3 empty() noexcept { return alg_tuple3(0, 0); }

#pragma region construct_and_destruct

    inline constexpr alg_tuple3() noexcept {}

    template<typename num_type_1, typename num_type_2, typename num_type_3>
    inline constexpr alg_tuple3(num_type_1 v1, num_type_2 v2, num_type_3 v3) noexcept
    {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }

    template<typename other_alg3_type>
    inline constexpr alg_tuple3(const other_alg3_type& values) noexcept
    {
        v1 = values.v1;
        v2 = values.v2;
        v3 = values.v3;
    }

#pragma endregion

#pragma region methods

    template<c_f::concept_fundamental cast_type>
    inline constexpr auto as() const noexcept
    {
        return alg_tuple3<cast_type>(v1, v2, v3);
    }

#pragma endregion

#pragma region operators

    template<typename other_type>
    inline constexpr const alg_tuple3& operator=(const alg_tuple3<other_type>& other_tuple) noexcept
    {
        v1 = other_tuple.v1;
        v2 = other_tuple.v2;
        v3 = other_tuple.v3;
    }

    // ADDITION
    template<typename other_type>
    inline constexpr auto operator+(const alg_tuple3<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v1);

        return alg_tuple3<num_type>(v1 + other_tuple.v1, v2 + other_tuple.v2, v3 + other_tuple.v3);
    }

    template<typename numeric_type>
    inline constexpr auto operator+(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple3<num_type>(v1 + value, v2 + value, v3 + value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple3& operator+=(const alg_tuple3<other_type>& other_tuple
    ) noexcept
    {
        v1 += other_tuple.v1;
        v2 += other_tuple.v2;
        v3 += other_tuple.v3;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple3& operator+=(numeric_type value) noexcept
    {
        v1 += value;
        v2 += value;
        v3 += value;

        return *this;
    }

    // SUBSTRACTION
    template<typename other_type>
    inline constexpr auto operator-(const alg_tuple3<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v1);

        return alg_tuple3<num_type>(v1 - other_tuple.v1, v2 - other_tuple.v2, v3 - other_tuple.v3);
    }

    template<typename numeric_type>
    inline constexpr auto operator-(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple3<num_type>(v1 - value, v2 - value, v3 - value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple3& operator-=(const alg_tuple3<other_type>& other_tuple
    ) noexcept
    {
        v1 -= other_tuple.v1;
        v2 -= other_tuple.v2;
        v3 -= other_tuple.v3;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple3& operator-=(numeric_type value) noexcept
    {
        v1 -= value;
        v2 -= value;
        v3 -= value;

        return *this;
    }

    // MULTIPLICATION
    template<typename other_type>
    inline constexpr auto operator*(const alg_tuple3<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v1);

        return alg_tuple3<num_type>(v1 * other_tuple.v1, v2 * other_tuple.v2, v3 * other_tuple.v3);
    }

    template<typename numeric_type>
    inline constexpr auto operator*(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple3<num_type>(v1 * value, v2 * value, v3 * value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple3& operator*=(const alg_tuple3<other_type>& other_tuple
    ) noexcept
    {
        v1 *= other_tuple.v1;
        v2 *= other_tuple.v2;
        v3 *= other_tuple.v3;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple3& operator*=(numeric_type value) noexcept
    {
        v1 *= value;
        v2 *= value;
        v3 *= value;

        return *this;
    }

    // DIVISION
    template<typename other_type>
    inline constexpr auto operator/(const alg_tuple3<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v1);

        return alg_tuple3<num_type>(v1 / other_tuple.v1, v2 / other_tuple.v2, v3 / other_tuple.v3);
    }

    template<typename numeric_type>
    inline constexpr auto operator/(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple3<num_type>(v1 / value, v2 / value, v3 / value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple3& operator/=(const alg_tuple3<other_type>& other_tuple
    ) noexcept
    {
        v1 /= other_tuple.v1;
        v2 /= other_tuple.v2;
        v3 /= other_tuple.v3;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple3& operator/=(numeric_type value) noexcept
    {
        v1 /= value;
        v2 /= value;
        v3 /= value;

        return *this;
    }

    template<typename other_type>
    inline constexpr bool operator==(const alg_tuple3<other_type>& other_tuple) noexcept
    {
        return v1 == other_tuple.v1 && v2 == other_tuple.v2 && v3 == other_tuple.v3;
    }

    template<typename other_type>
    inline constexpr bool operator!=(const alg_tuple3<other_type>& other_tuple) noexcept
    {
        return v1 != other_tuple.v1 || v2 != other_tuple.v2 || v3 != other_tuple.v3;
    }

#pragma endregion
};

template<typename type_1, typename type_2, typename type_3>
alg_tuple3(type_1, type_2, type_3) -> alg_tuple3<c_f::senior_conversion_t<type_1, type_2, type_3>>;

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