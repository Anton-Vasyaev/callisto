// 3rd party
#include <glm/glm.hpp>
// project
#include <callisto/framework/utility/delta_timer.hpp>
#include <callisto/framework/containers.hpp>

#include <callisto/math/utility.hpp>

#include <callisto/graphics/visual.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;
namespace c_g = callisto::graphics;

class simple_triangle_processor : public c_g::a_window_processor
{
    c_g::gl_shader_program _shader_program;

    GLuint _vao;

    c_g::gl_location _rotate_stage_location;

    c_g::gl_location _offset_location;

    c_m::value_looper<float> _rotate_stage;

    glm::vec2 _offset_position;

    c_f::enum_map<c_g::key_type, bool> _pressed_keys;

    c_f::delta_timer _delta_timer;

    float _rotate_speed;

    // protected methods
    void process_control();

public:
    // construct and destruct
    inline simple_triangle_processor() {}

    virtual ~simple_triangle_processor();

    // a_window_processor implementation
    virtual void init(c_g::i_window_context& context) override;

    virtual void process(c_g::i_window_context& context) override;

    virtual void on_key_event(c_g::key_event data) override;

    virtual void on_mouse_button_event(c_g::mouse_button_event data) override;

    virtual void on_cursor_event(c_g::cursor_event data) override;

    virtual void on_change_position(c_m::point2i position) override;

    virtual void on_resize(c_m::size2i size) override;
};