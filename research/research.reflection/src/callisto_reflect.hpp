#pragma once

// clang-format off

#define CALLISTO_REFLECT(reflect_ob, value) \
    reflect_ob.reflect(value, L#value)

// clang-format on