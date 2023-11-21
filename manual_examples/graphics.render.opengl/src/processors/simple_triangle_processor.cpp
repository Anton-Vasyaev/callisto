// parent header
#include "simple_triangle_processor.hpp"
// std
#include <vector>

const char* vertex_shader_source
    = "   #version 330 core                                                       \n"
      "   layout(location = 0) in vec2 a_position;                                \n"
      "   layout(location = 1) in vec3 a_color;                                   \n"
      "                                                                           \n"
      "   out vec3 our_color;                                                     \n"
      "                                                                           \n"
      "   uniform float rotate_stage;                                             \n"
      "   uniform vec2  offset;                                                   \n"
      "                                                                           \n"
      "   void main()                                                             \n"
      "   {                                                                       \n"
      "       float angle = radians(rotate_stage * 360.0);                        \n"
      "       float a_cos = cos(angle);                                           \n"
      "       float a_sin = sin(angle);                                           \n"
      "                                                                           \n"
      "       float x = a_position.x;                                             \n"
      "       float y = a_position.y;                                             \n"
      "                                                                           \n"
      "       float x_rot = x * a_cos - y * a_sin + offset.x;                     \n"
      "       float y_rot = x * a_sin + y * a_cos + offset.y;                     \n"
      "       gl_Position = vec4(x_rot, y_rot, 0.0, 1.0);                         \n"
      "       our_color   = a_color;                                              \n"
      "   }                                                                       \n";

const char* fragment_shader_source
    = "   #version 330 core                                                       \n"
      "                                                                           \n"
      "   in vec3 our_color;                                                      \n"
      "                                                                           \n"
      "   out vec4 frag_color;                                                    \n"
      "                                                                           \n"
      "   void main()                                                             \n"
      "   {                                                                       \n"
      "       frag_color = vec4(our_color, 1.0);                                  \n"
      "   }                                                                       \n";

#pragma region private_methods

void simple_triangle_processor::process_control()
{
    auto delta = 0.4f * _delta_timer.delta();

    auto move_speed = 0.5f;

    if (_pressed_keys[c_g::key_type::w]) _offset_position.y += delta * move_speed;
    if (_pressed_keys[c_g::key_type::s]) _offset_position.y -= delta * move_speed;
    if (_pressed_keys[c_g::key_type::a]) _offset_position.x += delta * move_speed;
    if (_pressed_keys[c_g::key_type::d]) _offset_position.x -= delta * move_speed;
}

#pragma endregion

#pragma region construct_and_destruct

simple_triangle_processor::~simple_triangle_processor() {}

#pragma endregion

#pragma region a_window_processor_implementation

void simple_triangle_processor::init(c_g::i_window_context& context)
{
    glDisable(GL_DEPTH_TEST);

    _rotate_stage = c_m::value_looper<float>(0.0, 0.0, 1.0);
    _rotate_speed = 0.01f;

    _offset_position.x = 0.0f;
    _offset_position.y = 0.0f;

    auto vertex_shader   = c_g::gl_shader(vertex_shader_source, c_g::gl_shader_type::vertex);
    auto fragment_shader = c_g::gl_shader(fragment_shader_source, c_g::gl_shader_type::fragment);

    _shader_program = c_g::gl_shader_program(vertex_shader, fragment_shader);

    _rotate_stage_location = _shader_program.get_uniform_location("rotate_stage");
    _offset_location       = _shader_program.get_uniform_location("offset");

    auto data = std::vector<float> { 0.0f, 0.5f, 1.0f,  0.0f,  0.0f, 0.5f, -0.5f, 0.0f,
                                     1.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f };

    auto indices = std::vector<uint32_t> { 0, 1, 2 };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(uint32_t),
        indices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
    _vao = vao;

    _delta_timer.start();
}

void simple_triangle_processor::process(c_g::i_window_context& context)
{
    _delta_timer.tick();

    process_control();

    // opengl drawing
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _rotate_stage += _delta_timer.delta() * _rotate_speed;

    _shader_program.use();

    _rotate_stage_location.uniform_1f(_rotate_stage);
    _offset_location.uniform_2f(_offset_position);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Dear ImGui drawing
    ImGui::Begin("Settings");
    {
        ImGui::SliderFloat("rotate speed", &_rotate_speed, -1.0, 1.0);
        ImGui::SliderFloat("offset x", &_offset_position.x, -1.0, 1.0);
        ImGui::SliderFloat("offset y", &_offset_position.y, -1.0, 1.0);
    }
    ImGui::End();
}

void simple_triangle_processor::on_key_event(c_g::key_event data)
{
    if (data.action == c_g::input_action::press) _pressed_keys[data.key] = true;
    else if (data.action == c_g::input_action::release) _pressed_keys[data.key] = false;
}

void simple_triangle_processor::on_mouse_button_event(c_g::mouse_button_event data) {}

void simple_triangle_processor::on_cursor_event(c_g::cursor_event data) {}

void simple_triangle_processor::on_change_position(c_m::point2i position) {}

void simple_triangle_processor::on_resize(c_m::size2i size) {}

#pragma endregion