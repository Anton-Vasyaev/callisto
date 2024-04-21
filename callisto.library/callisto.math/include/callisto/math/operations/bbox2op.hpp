#pragma once

#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct bbox2op
{
    template<typename type>
    inline static constexpr auto normalize(const bbox2<type>& box, const bbox2<type>& contour)
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

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<typename type>
    inline static constexpr auto
    reverse_normalize(const bbox2<type>& box, const bbox2<type>& contour)
    {
        auto contour_w = contour.width();
        auto contour_h = contour.height();

        auto x1 = box.x1 * contour_w + contour.x1;
        auto y1 = box.y1 * contour_h + contour.y1;

        auto x2 = box.x2 * contour_w + contour.x1;
        auto y2 = box.y2 * contour_h + contour.y1;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<typename type>
    inline static constexpr auto center(const bbox2<type>& box)
    {
        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        auto x_center = (x1 + x2) / 2;
        auto y_center = (y1 + y2) / 2;

        return point2<type>(x_center, y_center);
    }

    template<typename type>
    inline static constexpr auto scale(const bbox2<type>& box, size2<type> scale_size)
    {
        auto x_scale = scale_size.x;
        auto y_scale = scale_size.y;

        auto center_point = bbox2op::center(box);

        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        x1 = (x1 - center_point.x) * x_scale + center_point.x;
        y1 = (y1 - center_point.y) * y_scale + center_point.y;

        x2 = (x2 - center_point.x) * x_scale + center_point.x;
        y2 = (y2 - center_point.y) * y_scale + center_point.y;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<c_f::concept_arithmetic type>
    inline static constexpr auto move(const bbox2<type>& box, const vector2<type>& move_vector)
    {
        auto x1 = box.x1 + move_vector.x;
        auto y1 = box.y1 + move_vector.y;

        auto x2 = box.x2 + move_vector.x;
        auto y2 = box.y2 + move_vector.y;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<c_f::concept_arithmetic type>
    inline static constexpr auto from_center(point2<type> center, size2<type> size)
    {
        auto x1 = center.x - size.width / 2.0;
        auto y1 = center.y - size.height / 2.0;

        auto x2 = center.x + size.width / 2.0;
        auto y2 = center.y + size.height / 2.0;

        return bbox2<type>(x1, y1, x2, y2);
    };
};

} // namespace callisto::math