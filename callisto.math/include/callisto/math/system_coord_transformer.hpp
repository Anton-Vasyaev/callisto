#pragma once

namespace callisto::math
{

template<typename _coord_type>
class base_system_coord_transformer
{
public:
    using coord_type = _coord_type;

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
    inline base_system_coord_transformer(
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
        this->src_width  = src_right  - src_left;
        this->src_height = src_bottom - src_top;

        this->dst_left   = dst_left;
        this->dst_top    = dst_top;
        this->dst_width  = dst_right  - dst_left;
        this->dst_height = dst_bottom - dst_top;
    }

    template<typename point_type>
    inline point_type normalize(point_type point)
    {
        coord_type x = point.x;
        coord_type y = point.y;

        x = (x - this->src_left) / this->src_width;
        y = (y - this->src_top)  / this->src_height;

        x = x * this->dst_width  + this->dst_left;
        y = y * this->dst_height + this->dst_top;

        return point_type(x, y);
    }

    template<typename point_type>
    inline point_type operator()(point_type point)
    {
        return this->normalize(point);
    }
};

using system_coord_transformer_f = base_system_coord_transformer<float>;
using system_coord_transformer_d = base_system_coord_transformer<double>;


};