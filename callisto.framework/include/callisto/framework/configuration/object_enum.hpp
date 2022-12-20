#pragma once

// std
#include <type_traits>
#include <array>
// 3rd party
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace callisto::framework
{

// Classes, traits and concept for object enum compile-time identification.
class object_enum
{
};

template<typename type>
struct is_object_enum
{
    static constexpr bool value = std::is_base_of_v<object_enum, type>;
};

template<typename type>
constexpr bool is_object_enum_v = is_object_enum<type>::value;

template<typename type>
concept concept_object_enum = is_object_enum_v<type>;

/// @brief Pair of enum value description: integer code and str present.
class enum_value_description
{
    int         _code;
    const char* _str;

public:
    /// @brief Construct
    /// @param code Integer code.
    /// @param str String present.
    constexpr enum_value_description(int code, const char* str) : _code(code), _str(str) {}

    /// @brief Return integer code.
    /// @return Integer code.
    constexpr int get_code() const { return _code; }

    /// @brief Return string present.
    /// @return String present.
    constexpr const char* get_str() const { return _str; }
};

// clang-format off

// Define field with only name.
#define _DEFINE_ENUM_VALUE_ONLY_NAME(value)                     \
    BOOST_PP_VARIADIC_TO_SEQ(BOOST_PP_TUPLE_ELEM(1, 0, value))  \


// Define field with name and value.
#define _DEFINE_ENUM_VALUE_NAME_AND_KEY(value)                                                      \
    BOOST_PP_VARIADIC_TO_SEQ(BOOST_PP_TUPLE_ELEM(2, 0, value) = BOOST_PP_TUPLE_ELEM(2, 1, value))   \


// Define selector for enum field defining.
#define _DEFINE_ENUM_VALUE(r, data, value)              \
    BOOST_PP_IF(                                        \
        BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(value), 2),  \
        _DEFINE_ENUM_VALUE_NAME_AND_KEY(value),         \
        _DEFINE_ENUM_VALUE_ONLY_NAME(value)             \
    )                                                   \


// Define fields.
#define _DEFINE_ENUM_VALUES(...)                                                                            \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(_DEFINE_ENUM_VALUE, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))  \


// Define methods who return enum field wrap data.
#define _DEFINE_ENUM_VALUE_METHOD(r, type_name, value)                          \
    inline static constexpr type_name BOOST_PP_TUPLE_ELEM(0, value)() noexcept  \
    {                                                                           \
        return type_name(inner::BOOST_PP_TUPLE_ELEM(0, value));                 \
    }                                                                           \


// Define case-statement for str() method.
#define _DEFINE_TO_STR_CASE(r, type_name, value_name)                                                               \
    case inner::BOOST_PP_TUPLE_ELEM(0, value_name): return BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, value_name));  \


// Define str() method.
#define _DEFINE_TO_STR_METHOD(type_name, ...)                                                               \
    constexpr const char* str() const noexcept                                                              \
    {                                                                                                       \
        switch(_enum_data)                                                                                  \
        {                                                                                                   \
            BOOST_PP_SEQ_FOR_EACH(_DEFINE_TO_STR_CASE, type_name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))    \
            default: return "";                                                                             \
        }                                                                                                   \
    }                                                                                                       \


// Define case-statement in validate() method.
#define _DEFINE_VALIDATE_METHOD_CASE(r, type_name, value_name)  \
    case inner::BOOST_PP_TUPLE_ELEM(0, value_name):             \


// Define validate method.
#define _DEFINE_VALIDATE_METHOD(type_name, ...)                                                                     \
    constexpr bool validate() const noexcept                                                                        \
    {                                                                                                               \
        switch(_enum_data)                                                                                          \
        {                                                                                                           \
            BOOST_PP_SEQ_FOR_EACH(_DEFINE_VALIDATE_METHOD_CASE, type_name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))   \
                return true;                                                                                        \
            default:                                                                                                \
                return false;                                                                                       \
        }                                                                                                           \
    }                                                                                                               \


// Define value description constructor initialize.
#define _DEFINE_VALUE_DESCRIPTION(r, type_name, value)                          \
    (                                                                           \
        callisto::framework::enum_value_description(                            \
            static_cast<int>(inner::BOOST_PP_TUPLE_ELEM(0, value)),             \
            BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, value))                   \
        )                                                                       \
    )                                                                           \


// Enumerate enum_value_description in initializer brackets.
#define DEFINE_VALUES_DESCRIPTION(type_name, ...)                                                                           \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(_DEFINE_VALUE_DESCRIPTION, type_name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))   \



/// @brief Preprocessor macros for define object-like enum.
///        Fields of enum enumerating.
/// @param type_name      Name of enum type.
/// @param enum_functions Functions of enum.
/// @param unknown_field  Description of unknown field.
/// @param __VA_ARGS__    Description of fields.
#define CALLISTO_DEFINE_OBJECT_ENUM(type_name, enum_functions, unknown_field, ...)                                                              \
    class type_name : public callisto::framework::object_enum                                                                                   \
    {                                                                                                                                           \
    public:                                                                                                                                     \
        /* Real enum values. */                                                                                                                 \
        enum class inner                                                                                                                        \
        {                                                                                                                                       \
            _DEFINE_ENUM_VALUES(unknown_field),                                                                                                 \
            _DEFINE_ENUM_VALUES(__VA_ARGS__)                                                                                                    \
        };                                                                                                                                      \
                                                                                                                                                \
    private:                                                                                                                                    \
        /* Define values descriptions. */                                                                                                       \
        static constexpr std::array<                                                                                                            \
            callisto::framework::enum_value_description,                                                                                        \
            BOOST_PP_SEQ_SIZE(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                                                            \
        > _values_descriptions                                                                                                                  \
        {                                                                                                                                       \
            BOOST_PP_SEQ_ENUM(                                                                                                                  \
                BOOST_PP_SEQ_FOR_EACH(                                                                                                          \
                    _DEFINE_VALUE_DESCRIPTION,                                                                                                  \
                    type_name,                                                                                                                  \
                    BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)                                                                                       \
                )                                                                                                                               \
            )                                                                                                                                   \
        };                                                                                                                                      \
                                                                                                                                                \
    public:                                                                                                                                     \
        /* Return name of enum. */                                                                                                              \
        static constexpr const char* get_enum_name() noexcept                                                                                   \
        {                                                                                                                                       \
            return BOOST_PP_STRINGIZE(type_name);                                                                                               \
        }                                                                                                                                       \
                                                                                                                                                \
        /* Values descriptions getter. */                                                                                                       \
        static constexpr auto& get_values_descriptions() noexcept                                                                               \
        {                                                                                                                                       \
            return _values_descriptions;                                                                                                        \
        }                                                                                                                                       \
                                                                                                                                                \
        /* Return inner enum data. */                                                                                                           \
        constexpr inner get_data() const noexcept                                                                                               \
        {                                                                                                                                       \
            return _enum_data;                                                                                                                  \
        }                                                                                                                                       \
                                                                                                                                                \
        /* Values methods. */                                                                                                                   \
        _DEFINE_ENUM_VALUE_METHOD(0, type_name, unknown_field)                                                                                  \
        BOOST_PP_SEQ_FOR_EACH(_DEFINE_ENUM_VALUE_METHOD, type_name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                      \
                                                                                                                                                \
    private:                                                                                                                                    \
        inner _enum_data;                                                                                                                       \
                                                                                                                                                \
        constexpr inline type_name(inner enum_data) : _enum_data(enum_data) { }                                                                 \
                                                                                                                                                \
    public:                                                                                                                                     \
        /* Constructors. */                                                                                                                     \
        constexpr inline type_name() : _enum_data(inner::BOOST_PP_TUPLE_ELEM(0, unknown_field)) {}                                              \
                                                                                                                                                \
        constexpr inline explicit type_name(int val)                                                                                            \
        {                                                                                                                                       \
            _enum_data = static_cast<inner>(val);                                                                                               \
        }                                                                                                                                       \
                                                                                                                                                \
        /* String present method. */                                                                                                            \
        _DEFINE_TO_STR_METHOD(type_name, __VA_ARGS__)                                                                                           \
        /* Validate method. */                                                                                                                  \
        _DEFINE_VALIDATE_METHOD(type_name, __VA_ARGS__)                                                                                         \
                                                                                                                                                \
        /* Custom user functions. */                                                                                                            \
        enum_functions                                                                                                                          \
                                                                                                                                                \
                                                                                                                                                \
        /* Operators. */                                                                                                                        \
        inline constexpr bool operator==(type_name val) const noexcept                                                                          \
        {                                                                                                                                       \
            return _enum_data == val._enum_data;                                                                                                \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr bool operator!=(type_name val) const noexcept                                                                          \
        {                                                                                                                                       \
            return _enum_data != val._enum_data;                                                                                                \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr type_name operator|(type_name val) const noexcept                                                                      \
        {                                                                                                                                       \
            return type_name(static_cast<int>(_enum_data) | static_cast<int>(val._enum_data));                                                  \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr type_name& operator|=(type_name val) noexcept                                                                          \
        {                                                                                                                                       \
            *this = *this | val;                                                                                                                \
            return *this;                                                                                                                       \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr type_name operator&(type_name val) const noexcept                                                                      \
        {                                                                                                                                       \
            return type_name(static_cast<int>(_enum_data) & static_cast<int>(val._enum_data));                                                  \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr type_name& operator&=(type_name val) noexcept                                                                          \
        {                                                                                                                                       \
            *this = *this & val;                                                                                                                \
            return *this;                                                                                                                       \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr type_name operator^(type_name val) const noexcept                                                                      \
        {                                                                                                                                       \
            return type_name(static_cast<int>(_enum_data) ^ static_cast<int>(val._enum_data));                                                  \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr type_name& operator^=(type_name val) noexcept                                                                          \
        {                                                                                                                                       \
            *this = *this ^ val;                                                                                                                \
            return *this;                                                                                                                       \
        }                                                                                                                                       \
                                                                                                                                                \
        inline constexpr explicit operator int() const noexcept { return static_cast<int>(_enum_data); }                                        \
    };                                                                                                                                          \

}

// clang-format on