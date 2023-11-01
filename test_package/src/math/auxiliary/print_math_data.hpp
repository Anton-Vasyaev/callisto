#pragma once

// project
#include <callisto/math/primitives.hpp>

namespace c_m = callisto::math;

template<typename stream_type, typename type>
inline stream_type& operator<<(stream_type& stream, const c_m::alg_tuple2<type>& values)
{
    stream << "(" << values.v1 << ", " << values.v2 << ")";

    return stream;
}

template<typename stream_type, typename type>
inline stream_type& operator<<(stream_type& stream, const c_m::line2<type>& line)
{
    stream << "[" << line.x1 << ", " << line.y1 << ", " << line.x2 << ", " << line.y2 << "]";

    return stream;
}

template<typename stream_type, typename type>
inline stream_type& operator<<(stream_type& stream, const c_m::rectangle<type>& rect)
{
    stream << "[" << rect.position.x << ", " << rect.position.y << ", " << rect.size.width << ", "
           << rect.size.height << "]";

    return stream;
}
