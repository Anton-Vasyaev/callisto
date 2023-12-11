#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftstroke.h>
// project
#include <callisto/framework/types/assert_traits.hpp>

namespace callisto::graphics::freetype
{

class stroker
{
    // data
    FT_Stroker __handler = nullptr;

    // private methods
    void __move_from(stroker&& other_stroker);

    void __destroy();

public:
    // construct and destruct
    stroker(FT_Stroker handler);

    stroker(const stroker&) = delete;

    stroker(stroker&& stroker);

    ~stroker();

    // methods
    void
    set(FT_Fixed            radius,
        FT_Stroker_LineCap  line_cap,
        FT_Stroker_LineJoin line_join,
        FT_Fixed            miter_limit);

    // getters and setters
    FT_Stroker get_handler();

    const FT_Stroker get_handler() const;

    // operators
    stroker& operator=(const stroker&) = delete;

    stroker& operator=(stroker&& other_stroker);
};

CALLISTO_ASSERT_TRAIT_ONLY_MOVE(stroker);

} // namespace callisto::graphics::freetype