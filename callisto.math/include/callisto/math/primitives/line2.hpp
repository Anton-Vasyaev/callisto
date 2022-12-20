#pragma once

#include "alg_tuple2.hpp"


namespace callisto::math
{

// imports
namespace
{
    namespace c_f = callisto::framework;
}


template<typename _value_type>
struct line2
{
    using value_type = _value_type;

    using point_type = point2<value_type>;


    point_type start;

    point_type end;


    static inline constexpr line2 empty() { return line2(0, 0, 0, 0); }

#pragma region construct_and_destruct

    inline constexpr line2() { }

    template<
        typename start_x_type,
        typename start_y_type,
        typename end_x_type,
        typename end_y_type
    >
    inline constexpr line2(
        start_x_type start_x, 
        start_y_type start_y, 
        end_x_type end_x, 
        end_y_type end_y
    )
    {
        this->start.x = start_x;
        this->start.y = start_y;
        
        this->end.x = end_x;
        this->end.y = end_y;
    }

    template<typename start_type, typename end_type>
    inline constexpr line2(
        const start_type& start,
        const end_type&   end
    )
    {
        this->start = start;
        this->end   = end;
    }

#pragma endregion

#pragma region operators

    template<typename other_type>
    inline constexpr bool operator==(const line2<other_type>& other_line)
    {
        return this->start == other_line.start && this->end == other_line.end;
    }

    template<typename other_type>
    inline constexpr bool operator!=(const line2<other_type>& other_line)
    {
        return this->start != other_line.start || this->end != other_line.end;
    }

#pragma endregion

};

template<
    typename start_x_type,
    typename start_y_type,
    typename end_x_type,
    typename end_y_type
>
line2(start_x_type, start_y_type, end_x_type, end_y_type) -> line2<
    c_f::senior_conversion_t<start_x_type, start_y_type, end_x_type, end_y_type>
>;

template<typename start_type, typename end_type>
line2(start_type, end_type) -> line2<
    c_f::senior_conversion_t<
        typename start_type::value_type, 
        typename end_type::value_type
    >
>;




using line2i = line2<int32_t>;

using line2l = line2<int64_t>;

using line2f = line2<float>;

using line2d = line2<double>;

}