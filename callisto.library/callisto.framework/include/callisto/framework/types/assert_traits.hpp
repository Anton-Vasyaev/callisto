#pragma once

// project
#include "type_traits/is_only_movable.hpp"
#include "type_traits/is_only_referenceable.hpp"

// clang-format off

#define CALLISTO_ASSERT_TRAIT_ONLY_MOVE(class_name)                                             \
    static_assert(                                                                              \
        callisto::framework::is_only_movable_v<class_name>,                                     \
        "type \'" #class_name "\' is not only movable type. Delete copy constructor and "       \
        "copy assign operator. Add move constructor and move assign operator."                  \
    );


#define CALLISTO_ASSERT_TRAIT_ONLY_REFERENCE(class_name)                                            \
    static_assert(                                                                                  \
        callisto::framework::is_only_referenceable_v<class_name>,                                   \
        "type \'" #class_name "\' is not only referenceable type. Delete copy & move"               \
        "constructors and copy & move assign operators."                                            \
    );

// clang-format on