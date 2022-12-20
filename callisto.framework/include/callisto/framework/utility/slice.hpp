#pragma once

// std
#include <cstddef>
// project
#include <callisto/framework/concepts.hpp>

namespace callisto::framework
{
/// @brief Presents slice-data for array-like containers (strings, vectors, arrays)
class slice
{
private:
    size_t _start_val;

    size_t _end_val;

public:
    /// @brief Construct empty slice.
    inline constexpr slice() noexcept
    {
        _start_val = 0;
        _end_val   = 0;
    }

    /// @brief Constructs one-element slice.
    /// @tparam value_type Type of index.
    /// @param idx Index of element.
    template<concept_integer value_type>
    inline constexpr slice(value_type idx) noexcept
    {
        _start_val = idx;
        _end_val   = idx + 1;
    }

    /// @brief Constructs slice.
    /// @tparam start_type Type of start index.
    /// @tparam end_type Type of end index.
    /// @param start Start index.
    /// @param end End index.
    template<concept_integer start_type, concept_integer end_type>
    inline constexpr slice(start_type start, end_type end) noexcept
    {
        _start_val = start;
        _end_val   = end;
    }

#pragma endregion

#pragma region getters_and_setters

    /// @brief Checks the slice for emptiness
    /// @return Check status. true if slice is empty, false else.
    inline constexpr bool is_empty() const noexcept
    {
        return _start_val == _end_val && _start_val == 0;
    }

    /// @brief Returns start index of slice.
    /// @return Start index.
    inline constexpr size_t start() const noexcept { return _start_val; }

    /// @brief Returns end index of slice.
    /// @return End index.
    inline constexpr size_t end() const noexcept { return _end_val; }

#pragma endregion
};
} // namespace callisto::framework
