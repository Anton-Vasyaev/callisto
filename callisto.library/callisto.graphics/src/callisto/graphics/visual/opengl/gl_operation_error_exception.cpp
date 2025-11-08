// parent header
#include <callisto/graphics/visual/opengl/gl_operation_error_exception.hpp>

namespace callisto::graphics
{
namespace c_f = callisto::framework;

std::string gl_operation_error_exception::form_error_message() const
{
    return c_f::_bs(
        "error during call opengl function \'",
        __function_name,
        "\'. type:",
        gl_error_type_str(__error_type),
        "."
    );
}
} // namespace callisto::graphics