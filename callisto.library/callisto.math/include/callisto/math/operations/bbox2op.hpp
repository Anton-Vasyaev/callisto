#pragma once

#include <callisto/math/primitives.hpp>

namespace callisto::math
{

struct bbox2op
{
    template<typename bbox_type, typename contour_type>
    inline static constexpr auto
    normalize(const bbox2<bbox_type>& box, const bbox2<contour_type>& contour)
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

    template<typename bbox_type, typename contour_type>
    inline static constexpr auto
    reverse_normalize(const bbox2<bbox_type>& box, const bbox2<contour_type>& contour)
    {
        auto contour_w = contour.width();
        auto contour_h = contour.height();

        auto x1 = box.x1 * contour_w + contour.x1;
        auto y1 = box.y1 * contour_h + contour.y1;

        auto x2 = box.x2 * contour_w + contour.x1;
        auto y2 = box.y2 * contour_h + contour.y1;

        return bbox2(x1, y1, x2, y2);
    }

    template<typename type>
    inline static constexpr auto center(const bbox2<type>& box)
    {
        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        decltype(x1) x_center = (x1 + x2) / 2.0;
        decltype(x1) y_center = (y1 + y2) / 2.0;

        return point2<decltype(x1)>(x_center, y_center);
    }

    template<typename bbox_type, typename value_type>
    inline static constexpr auto scale(const bbox2<bbox_type>& box, size2<value_type> scale_size)
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

        return bbox2(x1, y1, x2, y2);
    }

    template<typename bbox_type, typename vec_type>
    inline static constexpr auto
    move(const bbox2<bbox_type>& box, const vector2<vec_type>& move_vector)
    {
        auto x1 = box.x1 + move_vector.x;
        auto y1 = box.y1 + move_vector.y;

        auto x2 = box.x2 + move_vector.x;
        auto y2 = box.y2 + move_vector.y;

        return bbox2(x1, y1, x2, y2);
    }

    template<c_f::concept_arithmetic value_type>
    inline static constexpr auto from_center(point2<value_type> center, size2<value_type> size)
    {
        auto x1 = center.x - size.width / 2.0;
        auto y1 = center.y - size.height / 2.0;

        auto x2 = center.x + size.width / 2.0;
        auto y2 = center.y + size.height / 2.0;

        return bbox2<value_type>(x1, y1, x2, y2);
    };
};

} // namespace callisto::math