#pragma once

// std
#include <cmath>
#include <span>
// project
#include <callisto/math/primitives/alg_tuple3.hpp>
#include <callisto/math/primitives/bbox3.hpp>
#include <callisto/framework/types/type_traits.hpp>
#include <callisto/math/functions.hpp>
// project
#include "auxiliary.hpp"

namespace callisto::math
{
struct point3op
{
    template<typename type>
    inline static constexpr bbox3<type> get_box_contour(std::span<point3<type>> points)
    {
        type min_x = points[0].x;
        type max_x = points[0].x;

        type min_y = points[0].y;
        type max_y = points[0].y;

        type min_z = points[0].z;
        type max_z = points[0].z;

        for (auto& p : points)
        {
            min_x = min_f(min_x, p.x);
            max_x = max_f(max_x, p.x);

            min_y = min_f(min_y, p.y);
            max_y = max_f(max_y, p.y);

            min_z = min_f(min_z, p.z);
            max_z = max_f(max_z, p.z);
        }

        return bbox3<type>(min_x, min_y, min_z, max_x, max_y, max_z);
    }
};

} // namespace callisto::math