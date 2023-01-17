// parent header
#include <callisto/graphics/visual/opengl/gl_window_context.hpp>
// std
#include <iostream>
// 3rd party
#include <imgui.h>
// project
#include <callisto/framework/exception.hpp>

#include <callisto/graphics/input/data.hpp>

#include <callisto/graphics/visual/opengl/third_party/imgui_impl_glfw.hpp>
#include <callisto/graphics/visual/opengl/third_party/imgui_impl_opengl3.hpp>
#include <callisto/graphics/visual/opengl/data.hpp>

#include <callisto/graphics/visual/opengl/auxiliary/input_auxiliary.hpp>

namespace c_m = callisto::math;

namespace callisto::graphics
{

std::unordered_map<GLFWwindow*, gl_window_context*> gl_window_context::call_functions;

std::mutex gl_window_context::call_functions_mutex;

#pragma region helpers

void GLAPIENTRY opengl_debug_message_callback(
    GLenum        source,
    GLenum        type,
    GLuint        id,
    GLenum        severity,
    GLsizei       length,
    const GLchar* message,
    const void*   userParam
)
{
    std::cout << "GL CALLBACK ["
              << "source:" << gl_debug_source::from_original(source).str() << "; "
              << "type:" << gl_debug_type::from_original(type).str() << "; "
              << "siverity:" << gl_debug_severity::from_original(severity).str() << "; "
              << "id:" << id << "]: " << message << "\n";
}

#pragma endregion

#pragma region static_callbacks

void gl_window_context::context_key_callback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods
)
{
    gl_window_context* window_context = call_functions.at(window);
    window_context->key_processing(key, scancode, action, mods);
}

void gl_window_context::context_cursor_position_callback(
    GLFWwindow* window,
    double      xpos,
    double      ypos
)
{
    gl_window_context* window_context = call_functions.at(window);
    window_context->cursor_position_processing(xpos, ypos);
}

void gl_window_context::context_mouse_button_callback(
    GLFWwindow* window,
    int         button,
    int         action,
    int         mods
)
{
    gl_window_context* window_context = call_functions.at(window);
    window_context->mouse_button_processing(button, action, mods);
}

void gl_window_context::change_position_callback(GLFWwindow* window, int x_pos, int y_pos)
{
    auto window_context = call_functions.at(window);
    window_context->position_processing(x_pos, y_pos);
}

void gl_window_context::resize_callback(GLFWwindow* window, int width, int height)
{
    gl_window_context* window_context = call_functions.at(window);
    window_context->resize_processing(width, height);
}

void gl_window_context::context_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    auto window_context = call_functions.at(window);

    window_context->viewport_value = c_m::size2i(width, height);

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}

#pragma endregion

#pragma region processing

void gl_window_context::processing()
{
    while (this->processing_flag && !glfwWindowShouldClose(this->window_handler))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->window_processor->process(*this);
        this->processing_signal_handler(*this);

        ImGui::Render();
        auto draw_data = ImGui::GetDrawData();
        if (draw_data) ImGui_ImplOpenGL3_RenderDrawData(draw_data);

        glfwSwapBuffers(this->window_handler);
    }
}

void gl_window_context::key_processing(int key, int scancode, int action, int mods)
{
    key_event event;
    event.key    = static_cast<key_type>(key);
    event.action = input_types_auxiliary::get_input_action_from_glfw(action);

    if (this->window_processor != nullptr) this->window_processor->on_key_event(event);
    this->key_event_signal_handler(event);
}

void gl_window_context::cursor_position_processing(double xpos, double ypos)
{
    cursor_event event;
    event.x = xpos;
    event.y = ypos;

    if (this->window_processor != nullptr) this->window_processor->on_cursor_event(event);
    this->cursor_event_signal_handler(event);
}

void gl_window_context::mouse_button_processing(int button, int action, int mods)
{
    mouse_button_event event;
    event.button = static_cast<mouse_button>(button);
    event.action = input_types_auxiliary::get_input_action_from_glfw(action);

    if (this->window_processor != nullptr) this->window_processor->on_mouse_button_event(event);
    this->mouse_button_event_signal_handler(event);
}

void gl_window_context::position_processing(int x_pos, int y_pos)
{
    auto pos                    = c_m::point2i { x_pos, y_pos };
    this->options.area.position = pos;

    if (this->window_processor != nullptr) this->window_processor->on_change_position(pos);
    this->change_position_signal_handler(pos);
}

void gl_window_context::resize_processing(int width, int height)
{
    auto size               = c_m::size2i { width, height };
    this->options.area.size = size;

    if (this->window_processor != nullptr) this->window_processor->on_resize(size);
    this->resize_signal_handler(size);
}

#pragma endregion

#pragma region construct_and_destruct

gl_window_context::gl_window_context() {}

gl_window_context::~gl_window_context()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (this->window_handler != nullptr) glfwDestroyWindow(this->window_handler);
}

#pragma endregion

#pragma region interface_signals

c_f::signal<void(key_event)>& gl_window_context::key_event_signal()
{
    return this->key_event_signal_handler;
}

c_f::signal<void(mouse_button_event)>& gl_window_context::mouse_button_event_signal()
{
    return this->mouse_button_event_signal_handler;
}

c_f::signal<void(cursor_event)>& gl_window_context::cursor_event_signal()
{
    return this->cursor_event_signal_handler;
}

c_f::signal<void(c_m::point2i)>& gl_window_context::change_position_signal()
{
    return this->change_position_signal_handler;
}

c_f::signal<void(c_m::size2i)>& gl_window_context::resize_signal()
{
    return this->resize_signal_handler;
}

c_f::signal<void(i_window_context&)>& gl_window_context::processing_signal()
{
    return this->processing_signal_handler;
}

#pragma endregion

#pragma region interface_impl

c_m::rectangle_i gl_window_context::get_area() const { return this->options.area; }

c_m::size2i gl_window_context::get_viewport() const { return this->viewport_value; }

window_mode gl_window_context::gl_window_context::get_window_mode() const
{
    return this->options.mode;
}

void gl_window_context::set_processor(std::shared_ptr<a_window_processor> processor)
{
    this->window_processor = processor;
}

void gl_window_context::start_processing()
{

    if (this->window_handler == nullptr) throw std::runtime_error("GLFW window is not initialized");
    {
        std::lock_guard<std::mutex> locker(call_functions_mutex);
        call_functions.insert(std::unordered_map<GLFWwindow*, gl_window_context*>::value_type(
            this->window_handler,
            this
        ));
    }

    if(this->window_processor == nullptr)
    {
        throw c_f::runtime_exception()
            << c_f::error_tag_message("Window processor is not setted.");
    }

    glfwMakeContextCurrent(this->window_handler);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { throw std::exception("Failed to initialize glew"); }
    std::cout << "Vendor name:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Version:" << glGetString(GL_VERSION) << std::endl;

    // CHECK. для интеропа между GLFW и  IMGUI
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    const char* glsl_version = "#version 410";

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->window_handler, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl_debug_message_callback, nullptr);

    glfwSetKeyCallback(this->window_handler, gl_window_context::context_key_callback);
    glfwSetCursorPosCallback(
        this->window_handler,
        gl_window_context::context_cursor_position_callback
    );
    glfwSetMouseButtonCallback(
        this->window_handler,
        gl_window_context::context_mouse_button_callback
    );

    glfwSetWindowPosCallback(this->window_handler, gl_window_context::change_position_callback);
    glfwSetWindowSizeCallback(this->window_handler, gl_window_context::resize_callback);
    glfwSetFramebufferSizeCallback(
        this->window_handler,
        gl_window_context::context_framebuffer_size_callback
    );

    int width, height;
    glfwGetFramebufferSize(this->window_handler, &width, &height);
    glViewport(0, 0, width, height);
    this->viewport_value = c_m::size2i(width, height);

    this->window_processor->init(*this);

    this->processing_flag = true;

    this->processing();
}

void gl_window_context::stop_processing() { this->processing_flag = false; }

} // namespace callisto::graphics