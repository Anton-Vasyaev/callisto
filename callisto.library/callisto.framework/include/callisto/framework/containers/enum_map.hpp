#pragma once

// std
#include <cstdint>
#include <limits>
#include <vector>
// project
#include <callisto/framework/types/type_traits/enum_limits.hpp>

namespace callisto::framework
{

/// @brief Provides fast access by key in the form of an enum.
///        For enum must declare enum_limits<_enum_type> class information with constexpr methods
///        ::lowest() and ::max() and field is_specialized set to true.
/// @tparam _enum_type  Type of enum key.
/// @tparam _store_type Type of stored value.
template<typename enum_type_t, typename store_type_t>
class enum_map
{
public:
    /// @brief Type of enum key.
    using enum_type = enum_type_t;

    /// @brief Type of storer value.
    using store_type = store_type_t;

private:
    static constexpr int64_t low_value
        = static_cast<int64_t>(std::enum_limits<enum_type>::lowest());

    static constexpr int64_t max_value
        = static_cast<int64_t>(std::enum_limits<enum_type>::max());

    static constexpr int64_t offset = -low_value;

public:
    /// @brief Size of container for store enum keys and values.
    ///        For checking container real size in bytes, calculate ::size * sizeof(_enum_type).
    static constexpr int64_t size = max_value - low_value;

private:
    std::vector<store_type> __data;

public:
    /// @brief Constructs a new object of @ref enum_map
    enum_map()
    {
        static_assert(
            std::enum_limits<enum_type>::is_specialized,
            "need specialization std::enum_limits for enum"
        );
        

        __data.resize(size);
    }

    /// @brief Returns value (rvalue or lvalue specified by vector<_enum_type> realisation).
    /// @param value Key of enum.
    /// @return Stored value.
    decltype(auto) operator[](enum_type value) &
    {
        return __data[static_cast<int>(value) + offset];
    }

    /// @brief Returns const value (rvalue or lvalue specified by bector<_enum_type> realisation).
    /// @param value Key of enum.
    /// @return Stored value.
    decltype(auto) operator[](enum_type value) const&
    {
        return __data[static_cast<int>(value) + offset];
    }
};

} // namespace callisto::framework