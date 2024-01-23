#pragma once

#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct bbox2op
{
    template<typename bbox_type, typename contour_type>
    inline static constexpr auto normalize(const bbox2<bbox_type>& box, const bbox2<contour_type>& contour)
    {
        auto w = contour.width();
        auto h = contour.height();

        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        x1 = (x1 - contour.x1) / w;
        y1 = (y1 - contour.y1) / h;

        x2 = (x2 - contour.x1) / w;
        y2 = (y2 - contour.y1) / h;

        return bbox2<bbox_type>(x1, y1, x2, y2);
    }
};

} // namespace callisto::math