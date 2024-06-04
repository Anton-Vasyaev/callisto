#pragma once

#include <callisto/math/primitives/alg_tuple2.hpp>

namespace callisto::math
{

template<typename type_t>
class base_system_coord_transformer
{
public:
    using type = type_t;

    using coord_type = point2<type>;

private:
    coord_type src_left;

    coord_type src_top;

    coord_type src_width;

    coord_type src_height;

    coord_type dst_left;

    coord_type dst_top;

    coord_type dst_width;

    coord_type dst_height;

public:
    base_system_coord_transformer(
        coord_type src_left,
        coord_type src_top,
        coord_type src_right,
        coord_type src_bottom,
        coord_type dst_left,
        coord_type dst_top,
        coord_type dst_right,
        coord_type dst_bottom
    )
    {
        this->src_left   = src_left;
        this->src_top    = src_top;
        this->src_width  = src_right - src_left;
        this->src_height = src_bottom - src_top;

        this->dst_left   = dst_left;
        this->dst_top    = dst_top;
        this->dst_width  = dst_right - dst_left;
        this->dst_height = dst_bottom - dst_top;
    }

    coord_type normalize(coord_type point)
    {
        coord_type x = point.x;
        coord_type y = point.y;

        x = (x - src_left) / src_width;
        y = (y - src_top) / src_height;

        x = x * dst_width + dst_left;
        y = y * dst_height + dst_top;

        return coord_type(x, y);
    }

    coord_type operator()(coord_type point) { return normalize(point); }
};

using system_coord_transformer_f = base_system_coord_transformer<float>;
using system_coord_transformer_d = base_system_coord_transformer<double>;

}; // namespace callisto::math