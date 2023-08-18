#pragma once

// std
#include <cstddef>
// project
#include <callisto/framework/concepts.hpp>

namespace callisto::framework
{
/// @brief Presents slice with step.
class step_slice
{
private:
    size_t _start_val;

    size_t _end_val;

    size_t _step_val;

public:
    /// @brief Constructs empty step slice.
    inline constexpr step_slice() noexcept
    {
        _start_val = 0;
        _end_val   = 0;
        _step_val  = 1;
    }

    /// @brief Constructs one-element step slice with single step.
    /// @tparam value_type Type of index.
    /// @param idx Index of element.
    template<concept_integer value_type>
    inline constexpr step_slice(value_type idx) noexcept
    {
        _start_val = idx;
        _end_val   = idx + 1;
        _step_val  = 1;
    }

    /// @brief Constructs step slice with single step.
    /// @tparam start_type Type of start index.
    /// @tparam end_type Type of end index.
    /// @param start Start index.
    /// @param end End index.
    template<concept_integer start_type, concept_integer end_type>
    inline constexpr step_slice(start_type start, end_type end) noexcept
    {
        _start_val = start;
        _end_val   = end;

        if (start <= end) _step_val = 1;
        else _step_val = -1;
    }

    /// @brief Constructs step slice
    /// @param start Start index.
    /// @param end End index.
    /// @param step Step.
    inline constexpr step_slice(size_t start, size_t end, size_t step) noexcept
    {
        _start_val = start;
        _end_val   = end;
        _step_val  = step;
    }

#pragma endregion

#pragma region getters_and_setters

    /// @brief Checks the slice for emptiness
    /// @return Check status. true if slice is empty, false else.
    inline constexpr bool is_empty() const noexcept
    {
        return _start_val == _end_val && _start_val == 0;
    }

    /// @brief Returns start index of step slice.
    /// @return Start index.
    inline constexpr size_t start() const noexcept { return _start_val; }

    /// @brief Returns end index of step slice.
    /// @return End index.
    inline constexpr size_t end() const noexcept { return _end_val; }

    /// @brief Returns step of slice.
    /// @return Step.
    inline constexpr size_t step() const noexcept { return _step_val; }

#pragma endregion
};
} // namespace callisto::framework
