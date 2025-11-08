#pragma once

// std
#include <vector>

namespace callisto::framework
{

/// @brief Provides a buffer based on ring-queue.
/// @tparam _type Type of stored value.
template<typename type_t>
class ring_buffer
{
public:
    /// @brief Type of stored value.
    using type = type_t;

private:
    std::vector<type> __buffer;

    size_t __head = 0;

    size_t __tail = 0;

    void increment_head() { __head = (__head + 1) % __buffer.size(); }

    void increment_tail()
    {
        __tail = (__tail + 1) % __buffer.size();

        if (__tail == __head) increment_head();
    }

public:
    ring_buffer() = delete;

    /// @brief Constructs a new object of @ref ring_buffer
    /// @param size Size of buffer.
    explicit ring_buffer(size_t size) { __buffer.resize(size + 1); }

    /// @brief Copies the data to the buffer's last position.
    /// @param value Reference to the data.
    void add_value(const type& value)
    {
        __buffer[__tail] = value;
        increment_tail();
    }

    /// @brief Moves r-value data to the buffer's last position.
    /// @param value R-value reference to the data.
    void add_value(type&& value)
    {
        __buffer[__tail] = std::move(value);
        increment_tail();
    }

    /// @brief Copies data on first position  and remove him from buffer.
    /// @param value Reference, where data will be copied.
    /// @return Copy status. @c true if data was copied, else @c false .
    bool get_value(type& value)
    {
        if (__head == __tail) return false;

        value = __buffer[__head];

        increment_head();

        return true;
    }

    /// @brief Moves data on first position
    /// @param value Reference, where data will be moved.
    /// @return Move status. @c true if data was copied, else @c false .
    bool get_and_move_value(type& value)
    {
        if (__head == __tail) return false;

        value = std::move(__buffer[__head]);
        increment_head();

        return true;
    }
};

} // namespace callisto::framework