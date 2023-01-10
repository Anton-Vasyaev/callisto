// parent header
#include "examples.hpp"
// project
#include <callisto/framework/utility/stopwatch.hpp>
#include <callisto/opencv.hpp>
#include <callisto/graphics/freetype.hpp>

namespace c_f  = callisto::framework;
namespace c_cv = callisto::opencv;
namespace c_ft = callisto::graphics::freetype;

void call_example_standard()
{
    c_ft::library lib;

    auto face = lib.new_face("resources/freesans.ttf", 0);
    face.set_pixel_sizes(0, 12);

    auto start_char = 65;
    auto end_char   = 90;

    auto char_seq_len = end_char - start_char + 1;

    c_f::stopwatch sw;

    sw.start();
    for (auto char_idx = start_char; char_idx <= end_char; char_idx++)
    {
        auto glyph_idx = face.get_char_index(char_idx);
        face.load_glyph(glyph_idx, FT_LOAD_NO_BITMAP);

        auto face_h = face.get_handler();

        WRAP_CALL_FREETYPE_FUNC(FT_Render_Glyph, face_h->glyph, FT_RENDER_MODE_LCD);

        FT_Bitmap bitmap = face_h->glyph->bitmap;

        std::cout << "width:" << bitmap.width << "\n";
        std::cout << "pitch:" << bitmap.pitch << "\n";
        std::cout << "rows:" << bitmap.rows << "\n";
        std::cout << "pixel mode:" << c_ft::pixel_mode_str(bitmap.pixel_mode) << "\n";

        auto font_mat_rgb
            = cv::Mat(bitmap.rows, bitmap.width / 3, CV_8UC3, bitmap.buffer, bitmap.pitch);

        c_cv::imshow("debug", font_mat_rgb);
    }
    sw.stop();

    std::cout << "render " << char_seq_len << " symbols, time: " << sw.microseconds() << " mcs.\n";
}