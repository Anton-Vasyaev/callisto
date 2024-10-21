#pragma once

#include <callisto/framework/types/assert_traits.hpp>

// clang-format off

#define CALLISTO_LIFETIME_MOVE_DEFAULT(class_name)                                          \
    class_name(const class_name&) = delete;                                                 \
                                                                                            \
    class_name(class_name&&) noexcept = default;                                            \
                                                                                            \
    class_name& operator=(const class_name&) = delete;                                      \
                                                                                            \
    class_name& operator=(class_name&&) noexcept = default;                                 \
                                                                                            \
    static constexpr void callisto_placeholder_func_assert_train_only_move() noexcept       \
    {                                                                                       \
        CALLISTO_ASSERT_TRAIT_ONLY_MOVE(class_name);                                        \
    }


#define __CALLISTO_LIFETIME_MOVE_BODY(class_name)                                           \
    class_name(const class_name&) = delete;                                                 \
                                                                                            \
    class_name(class_name&& other) noexcept                                                 \
    {                                                                                       \
        __move_from(std::move(other));                                                      \
    }                                                                                       \
                                                                                            \
    class_name& operator=(const class_name&) = delete;                                      \
                                                                                            \
    class_name& operator=(class_name&& other) noexcept                                      \
    {                                                                                       \
        __destroy();                                                                        \
        __move_from(std::move(other));                                                      \
                                                                                            \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    static constexpr void callisto_placeholder_func_assert_train_only_move() noexcept       \
    {                                                                                       \
        CALLISTO_ASSERT_TRAIT_ONLY_MOVE(class_name);                                        \
    }


#define CALLISTO_LIFETIME_MOVE(class_name)      \
    ~class_name() noexcept                      \
    {                                           \
        __destroy();                            \
    }                                           \
                                                \
    __CALLISTO_LIFETIME_MOVE_BODY(class_name);  \


#define CALLISTO_LIFETIME_MOVE_VIRTUAL(class_name)  \
    virtual ~class_name() noexcept                  \
    {                                               \
        __destroy();                                \
    }                                               \
                                                    \
    __CALLISTO_LIFETIME_MOVE_BODY(class_name);


#define CALISTO_LIFETIME_REFERENCE(class_name)                                              \
    class_name(const class_name&) = delete;                                                 \
                                                                                            \
    class_name(class_name&&) noexcept = delete;                                             \
                                                                                            \
    class_name& operator=(const class_name&) = delete;                                      \
                                                                                            \
    class_name& operator=(class_name&&) noexcept = delete;                                  \
                                                                                            \
    static constexpr void callisto_placeholder_func_assert_train_only_reference() noexcept  \
    {                                                                                       \
        CALLISTO_ASSERT_TRAIT_ONLY_REFERENCE(class_name);                                   \
    }

// clang-format on