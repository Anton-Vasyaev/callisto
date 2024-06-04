#pragma once

// std
#include <cstddef>
#include <algorithm>
#include <array>

namespace callisto::framework
{
template<typename type, size_t n>
class mutable_array
{
public:
    using value_type = type;

    using iterator = value_type*;

    using const_iterator = const value_type*;

    using reverse_iterator = std::reverse_iterator<value_type*>;

    using const_reverse_iterator = std::reverse_iterator<const value_type*>;

    static const size_t array_size = n;

private:
    std::array<value_type, n> __data_array;

    size_t __mutable_size = 0;

    void __copy_from(const mutable_array& array) noexcept
    {
        std::copy_n(array.data_array, array.mutable_size, __data_array);
        __mutable_size = array.mutable_size;
    }

    void __move_from(mutable_array&& array) noexcept
    {
        __copy_from(array);
        array.mutable_size = 0;
    }

public:
    mutable_array() = default;

    mutable_array(const mutable_array& array) noexcept { __copy_from(array); }

    mutable_array(mutable_array&& array) noexcept { __move_from(std::move(array)); }

    void resize(size_t new_size)
    {
        if (new_size > array_size) throw std::bad_alloc();
        __mutable_size = new_size;
    }

    // getters and setters
    size_t size() const noexcept { return __mutable_size; }

    value_type* data() noexcept { return __data_array; }

    const value_type* data() const noexcept { return __data_array; }

    iterator begin() noexcept { return __data_array; }

    const_iterator begin() const noexcept { return __data_array; }

    iterator end() noexcept { return __data_array + __mutable_size; }

    const_iterator end() const noexcept { return __data_array + __mutable_size; }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<value_type*>(__data_array + __mutable_size);
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const value_type*>(__data_array + __mutable_size);
    }

    reverse_iterator rend() noexcept { return std::reverse_iterator<value_type*>(__data_array); }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const value_type*>(__data_array);
    }

    // operators
    mutable_array& operator=(const mutable_array& array) noexcept
    {
        __copy_from(array);

        return *this;
    }

    mutable_array& operator=(mutable_array&& array) noexcept
    {
        __move_from(std::move(array));

        return *this;
    }

    value_type& operator[](std::size_t index) noexcept { return __data_array[index]; }

    const value_type& operator[](std::size_t index) const noexcept { return __data_array[index]; }
};
} // namespace callisto::framework