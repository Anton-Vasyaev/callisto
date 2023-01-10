#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftstroke.h>

namespace callisto::graphics::freetype
{

class stroker
{
    FT_Stroker _handler = nullptr;

public:
    // deleted functions
    stroker(const stroker&) = delete;

    const stroker& operator=(const stroker&) = delete;

    const stroker& operator=(stroker&&) = delete;

    // construct and destruct
    stroker(FT_Stroker handler);

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
};

} // namespace callisto::graphics::freetype