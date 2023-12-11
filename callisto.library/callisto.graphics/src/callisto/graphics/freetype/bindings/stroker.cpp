// parent header
#include <callisto/graphics/freetype/bindings/stroker.hpp>
// std
#include <utility>

namespace callisto::graphics::freetype
{
#pragma region private_methods

void stroker::__move_from(stroker&& other_stroker)
{
    __handler               = other_stroker.__handler;
    other_stroker.__handler = nullptr;
}

void stroker::__destroy()
{
    if (__handler != nullptr)
    {
        FT_Stroker_Done(__handler);
    }

    __handler = nullptr;
}

#pragma endregion

#pragma region construct and destruct

stroker::stroker(FT_Stroker handler) { __handler = handler; }

stroker::stroker(stroker&& stroker) { __move_from(std::move(stroker)); }

stroker::~stroker() { __destroy(); }

#pragma endregion

#pragma region methods

void stroker::set(
    FT_Fixed            radius,
    FT_Stroker_LineCap  line_cap,
    FT_Stroker_LineJoin line_join,
    FT_Fixed            miter_limit
)
{
    FT_Stroker_Set(__handler, radius, line_cap, line_join, miter_limit);
}

#pragma endregion

#pragma region getters and setters

FT_Stroker stroker::get_handler() { return __handler; }

const FT_Stroker stroker::get_handler() const { return __handler; }

#pragma endregion

#pragma region operators

stroker& stroker::operator=(stroker&& other_stroker)
{
    __destroy();
    __move_from(std::move(other_stroker));

    return *this;
}

#pragma endregion

} // namespace callisto::graphics::freetype
