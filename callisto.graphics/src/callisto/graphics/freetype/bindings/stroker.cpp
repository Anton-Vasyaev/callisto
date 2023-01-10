// parent header
#include <callisto/graphics/freetype/bindings/stroker.hpp>

namespace callisto::graphics::freetype
{
#pragma region construct and destruct

stroker::stroker(FT_Stroker handler) { _handler = handler; }

stroker::stroker(stroker&& stroker)
{
    _handler         = stroker._handler;
    stroker._handler = nullptr;
}

stroker::~stroker()
{
    if (_handler != nullptr) { FT_Stroker_Done(_handler); }
}

#pragma endregion

#pragma region methods

void stroker::set(
    FT_Fixed            radius,
    FT_Stroker_LineCap  line_cap,
    FT_Stroker_LineJoin line_join,
    FT_Fixed            miter_limit
)
{
    FT_Stroker_Set(_handler, radius, line_cap, line_join, miter_limit);
}

#pragma endregion

#pragma region getters and setters

FT_Stroker stroker::get_handler() { return _handler; }

const FT_Stroker stroker::get_handler() const { return _handler; }

#pragma endregion

} // namespace callisto::graphics::freetype
