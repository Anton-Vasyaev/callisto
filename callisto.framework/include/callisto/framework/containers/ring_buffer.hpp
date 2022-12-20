#pragma once

// std
#include <vector>

namespace callisto::framework
{

/// @brief Provides a buffer based on ring-queue.
/// @tparam _type Type of stored value.
template<typename _type>
class ring_buffer
{
public:
    /// @brief Type of stored value.
    using type = _type;

private:
    std::vector<type> _buffer;

    size_t _head = 0;

    size_t _tail = 0;

    inline void increment_head() { _head = (_head + 1) % _buffer.size(); }

    inline void increment_tail()
    {
        _tail = (_tail + 1) % buffer.size();

        if (_tail == _head) increment_head();
    }

public:
    ring_buffer() = delete;

    /// @brief Constructs a new object of @ref ring_buffer
    /// @param size Size of buffer.
    inline ring_buffer(size_t size) { _buffer.resize(size + 1); }

    /// @brief Copies the data to the buffer's last position.
    /// @param value Reference to the data.
    inline void add_value(const type& value)
    {
        _buffer[_tail] = value;
        increment_tail();
    }

    /// @brief Moves r-value data to the buffer's last position.
    /// @param value R-value reference to the data.
    inline void add_value(type&& value)
    {
        _buffer[_tail] = std::move(value);
        increment_tail();
    }

    /// @brief Copies data on first position  and remove him from buffer.
    /// @param value Reference, where data will be copied.
    /// @return Copy status. @c true if data was copied, else @c false .
    inline bool get_value(type& value)
    {
        if (_head == _tail) return false;

        value = _buffer[_head];

        increment_head();

        return true;
    }

    /// @brief Moves data on first position
    /// @param value Reference, where data will be moved.
    /// @return Move status. @c true if data was copied, else @c false .
    inline bool get_and_move_value(type& value)
    {
        if (_head == _tail) return false;

        value = std::move(_buffer[_head]);
        increment_head();

        return true;
    }
};

} // namespace callisto::framework