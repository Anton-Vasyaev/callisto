#pragma once

#include <type_traits>
#include <vector>
#include <array>
#include <memory>
#include <optional>
#include <string>

namespace callisto::framework
{

// vector -----------------------------------------------------------------------------------------

template<typename type>
struct is_std_vector : std::false_type
{
};

template<typename type, typename alloc_type>
struct is_std_vector<std::vector<type, alloc_type>> : std::true_type
{
};

template<typename type>
constexpr bool is_std_vector_v = is_std_vector<type>::value;

// array ------------------------------------------------------------------------------------------

template<typename type>
struct is_std_array : std::false_type
{
};

template<typename type, std::size_t n>
struct is_std_array<std::array<type, n>> : std::true_type
{
};

template<typename type>
constexpr bool is_std_array_v = is_std_array<type>::value;

// containers -------------------------------------------------------------------------------------

template<typename type>
struct is_std_sequential_container
{
    static constexpr bool value = is_std_array_v<type> | is_std_vector_v<type>;
};

template<typename type>
constexpr bool is_std_sequential_container_v = is_std_sequential_container<type>::value;

// optional ---------------------------------------------------------------------------------------

template<typename type>
struct is_std_optional : std::false_type
{
};

template<typename type>
struct is_std_optional<std::optional<type>> : std::true_type
{
};

template<typename type>
constexpr bool is_std_optional_v = is_std_optional<type>::value;

// unique_ptr -------------------------------------------------------------------------------------

template<typename type>
struct is_std_unique_ptr : std::false_type
{
};

template<typename type, typename deleter_type>
struct is_std_unique_ptr<std::unique_ptr<type, deleter_type>> : std::true_type
{
};

template<typename type>
constexpr bool is_std_unique_ptr_v = is_std_unique_ptr<type>::value;

// shared_ptr -------------------------------------------------------------------------------------

template<typename type>
struct is_std_shared_ptr : std::false_type
{
};

template<typename type>
struct is_std_shared_ptr<std::shared_ptr<type>> : std::true_type
{
};

template<typename type>
constexpr bool is_std_shared_ptr_v = is_std_shared_ptr<type>::value;

// basic_string
// -------------------------------------------------------------------------------------

template<typename type>
struct is_std_basic_string : std::false_type
{
};

template<typename char_type, typename traits_type, typename alloc_type>
struct is_std_basic_string<std::basic_string<char_type, traits_type, alloc_type>> : std::true_type
{
};

template<typename type>
constexpr bool is_std_basic_string_v = is_std_basic_string<type>::value;

} // namespace callisto::framework