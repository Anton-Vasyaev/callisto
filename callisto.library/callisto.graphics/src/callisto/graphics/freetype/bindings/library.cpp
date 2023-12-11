// parent header
#include <callisto/graphics/freetype/bindings/library.hpp>
// project
#include <callisto/graphics/freetype/exception.hpp>

namespace callisto::graphics::freetype
{
#pragma region construct_and_destruct

library::library() { WRAP_CALL_FREETYPE_FUNC(FT_Init_FreeType, &_handler); }

library::~library()
{
    if (this->_handler != nullptr)
    {
        WRAP_CALL_FREETYPE_FUNC(FT_Done_FreeType, _handler);
    }
}

#pragma endregion

#pragma region methods

face library::new_face(const std::string_view filepath_name, FT_Long face_index)
{
    FT_Face face_handler = nullptr;

    WRAP_CALL_FREETYPE_FUNC(FT_New_Face, _handler, filepath_name.data(), face_index, &face_handler);

    return face(face_handler);
}

stroker library::new_stroker()
{
    FT_Stroker stroker_handler;
    WRAP_CALL_FREETYPE_FUNC(FT_Stroker_New, _handler, &stroker_handler);

    return stroker(stroker_handler);
}

#pragma endregion

#pragma region getters_and_setters

FT_Library library::get_handler() { return _handler; }

const FT_Library library::get_handler() const { return _handler; }

#pragma endregion
} // namespace callisto::graphics::freetype