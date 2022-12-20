#pragma once

// std
#include <cstdint>
#include <limits>
#include <vector>

namespace callisto::framework
{

/// @brief Provides fast access by key in the form of an enum.
///        For enum must declare numeric_limits<_enum_type> class information with constexpr methods
///        ::lowest() and ::max() and field is_specialized set to true.
/// @tparam _enum_type  Type of enum key.
/// @tparam _store_type Type of stored value.
template<typename _enum_type, typename _store_type>
class enum_map
{
public:
    /// @brief Type of enum key.
    using enum_type = _enum_type;

    /// @brief Type of storer value.
    using store_type = _store_type;

private:
    static constexpr int64_t low_value
        = static_cast<int64_t>(std::numeric_limits<enum_type>::lowest());

    static constexpr int64_t max_value
        = static_cast<int64_t>(std::numeric_limits<enum_type>::max());

    static constexpr int64_t offset = -low_value;

public:
    /// @brief Size of container for store enum keys and values.
    ///        For checking container real size in bytes, calculate ::size * sizeof(_enum_type).
    static constexpr int64_t size = max_value - low_value;

private:
    std::vector<_store_type> data;

public:
    /// @brief Constructs a new object of @ref enum_map
    enum_map()
    {
        /*
        static_assert(
            std::numeric_limits<enum_type>::is_specialized,
            "need specialization std::numeric_limits for enum"
        );
        */
        // ToDo
        std::cout << (int)std::numeric_limits<enum_type>::lowest() << std::endl;
        std::cout << (int)std::numeric_limits<enum_type>::max() << std::endl;

        this->data.resize(size);
    }

    /// @brief Returns value (rvalue or lvalue specified by vector<_enum_type> realisation).
    /// @param value Key of enum.
    /// @return Stored value.
    inline decltype(auto) operator[](enum_type value) &
    {
        return this->data[static_cast<int>(value) + offset];
    }

    /// @brief Returns const value (rvalue or lvalue specified by bector<_enum_type> realisation).
    /// @param value Key of enum.
    /// @return Stored value.
    inline decltype(auto) operator[](enum_type value) const&
    {
        return this->data[static_cast<int>(value) + offset];
    }
};

} // namespace callisto::framework