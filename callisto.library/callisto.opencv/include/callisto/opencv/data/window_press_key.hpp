#pragma once

// std
#include <cstdint>

namespace callisto::opencv
{

enum class window_press_key : std::uint8_t
{
    UNKNOWN = 0,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,

    //            codes
    escape,    // 27
    space,     // 32
    tilda,     // 96: ~ `
    tab,       // 9
    enter,     // 13
    backspace, // 8
    slashes,   // 92 | \ /
};

window_press_key window_press_key_from_code(int code);

} // namespace callisto::opencv