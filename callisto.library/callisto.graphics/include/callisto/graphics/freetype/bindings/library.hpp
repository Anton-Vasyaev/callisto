#pragma once

// std
#include <string_view>
// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// project
#include <callisto/framework/types/assert_traits.hpp>

#include "face.hpp"
#include "stroker.hpp"

namespace callisto::graphics::freetype
{

class library
{
    FT_Library _handler = nullptr;

public:
    // construct and destruct
    library();

    library(const library&) = delete;

    library(library&& lib) = delete;

    ~library();

    // methods
    face new_face(std::string_view filepath_name, FT_Long face_index);

    stroker new_stroker();

    // getters and setters
    FT_Library get_handler();

    const FT_Library get_handler() const;

    // operators
    const library& operator=(const library&) = delete;

    const library& operator=(library&&) = delete;
};

CALLISTO_ASSERT_TRAIT_ONLY_REFERENCE(library);

} // namespace callisto::graphics::freetype
