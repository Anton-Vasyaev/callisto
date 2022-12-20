#pragma once

// std
#include <cstdint>
#include <memory>

namespace callisto::framework
{
/// @brief std::unique_ptr type of align-allocated memory.
/// @tparam value_type Basic data type of memory present.
template<typename value_type>
using unique_memory_type = std::unique_ptr<value_type, void (*)(value_type*)>;

/// @brief Allocates aligned memory.
/// @param size Size of allocated memory in bytes.
/// @param aligned_size Align of memory in bytes.
/// @return Pointer to align-allocated memory.
void* mem_aligned_alloc(size_t size, size_t aligned_size) noexcept;

/// @brief Frees of aligned-memory.
/// @param pointer Pointer To align-allocated memory.
void mem_aligned_free(void* pointer) noexcept;

template<typename value_type, typename other_type>
unique_memory_type<value_type> cast_unique_memory(unique_memory_type<other_type>& memory)
{
    return unique_memory_type<value_type>((value_type*)memory.release(), aligned_free<value_type>);
};

/// @brief Allocates aligned type-present memory.
/// @tparam value_type Basic data type of memory present.
/// @param size Number of elements in memory block. Real size of memory in bytes calculated by
///             formula: @code{.cpp}size * sizeof(value_type)}. @endcode
/// @param aligned_size Align of memory in bytes.
/// @return Pointer to align-allocated type-present memory.
template<typename value_type>
value_type* aligned_alloc(size_t size, size_t aligned_size)
{
    auto ptr = mem_aligned_alloc(size * sizeof(value_type), aligned_size);

    if (ptr == nullptr) throw std::bad_alloc();

    return (value_type*)ptr;
}

/// @brief Frees of aligned type-present memory.
/// @tparam value_type Basic data type of memory present.
/// @param ptr Pointer to align-allocated type-present memory.
template<typename value_type>
void aligned_free(value_type* ptr) noexcept
{
    mem_aligned_free((void*)ptr);
}

/// @brief Allocates aligned type-memory and wrap to unique pointer.
/// @tparam value_type Basic data type of memory.
/// @param size Number of elements in memory block. Real size of memory in bytes calculated by
///             formula: @code{.cpp}size * sizeof(value_type)}. @endcode
/// @param aligned_size Align of memory in bytes.
/// @return std::unique-ptr with pointer to align-allocated type-present memory.
template<typename value_type>
unique_memory_type<value_type> make_align_unique_memory(size_t size, size_t aligned_size)
{
    return unique_memory_type<
        value_type>(aligned_alloc<value_type>(size, aligned_size), aligned_free<value_type>);
}

} // namespace callisto::framework