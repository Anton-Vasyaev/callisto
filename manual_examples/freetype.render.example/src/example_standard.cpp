// parent header
#include "examples.hpp"
// project
#include <callisto/framework/utility/stopwatch.hpp>
#include <callisto/opencv.hpp>
#include <callisto/graphics/freetype.hpp>
#include <callisto/graphics/typing/freetype.hpp>

namespace c_f  = callisto::framework;
namespace c_cv = callisto::opencv;
namespace c_ft = callisto::graphics::freetype;
namespace c_g  = callisto::graphics;

void call_example_standard()
{
    auto num_type = c_f::numeric_type::float32;

    std::cout << "key_type:" << c_f::numeric_type_str(num_type) << std::endl;

    c_ft::library lib;

    auto face = lib.new_face("resources/freesans.ttf", 0);

    std::vector<uint32_t> indexes;
    for (int32_t ch_i = 65; ch_i <= 90; ch_i++)
    {
        indexes.push_back(ch_i);
    }

    auto garniture = c_g::build_garniture_freetype(face, indexes, 64, FT_LOAD_TARGET_LCD);

    for (auto& char_code : indexes)
    {
        auto& symbol_data = garniture.get_symbol_data(char_code);

        c_cv::imshow("debug", symbol_data.get_bitmap());
    }
}