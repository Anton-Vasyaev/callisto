#include <callisto/framework/native/platform_detect.h>
// parent header
#include <callisto/graphics/visual/opengl/gl_window_context.hpp>
// std
#include <iostream>
#include <exception>
// 3rd party
#include <imgui.h>

#if defined(CALLISTO_OS_WINDOWS)
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3native.h>
// project
#include <callisto/framework/exception.hpp>
#include <callisto/framework/types/singleton.hpp>

#include <callisto/graphics/input/data.hpp>

#include <callisto/graphics/visual/opengl/third_party/imgui_impl_glfw.hpp>
#include <callisto/graphics/visual/opengl/third_party/imgui_impl_opengl3.hpp>
#include <callisto/graphics/visual/opengl/data.hpp>

#include <callisto/graphics/visual/opengl/auxiliary/input_auxiliary.hpp>

#include <callisto/graphics/visual/opengl/gl_monitor_context.hpp>
#include <callisto/graphics/visual/opengl/gl_info_provider.hpp>

namespace c_m = callisto::math;
namespace c_f = callisto::framework;

namespace callisto::graphics
{

namespace
{
std::mutex imgui_init_mutex;

bool imgui_init_flag = true;

void validate_samples_param(int value, int max_samples, std::string_view param_name)
{
    if (value > max_samples)
    {
        CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
            "invalid value of parameter \'",
            param_name,
            "\'. value > max samples of opengl context in this hardware: ",
            value,
            " > ",
            max_samples,
            "."
        );
    }
}

void validate_and_process_gl_options(gl_window_options& options)
{
    auto max_samples = gl_info_provider::get_instance().get_max_samples();
    validate_samples_param(
        options.gl_multisampling,
        max_samples,
        gl_window_options::PRESENTS::GL_MULTISAMPLING
    );

    validate_samples_param(
        options.canvas_multisampling,
        max_samples,
        gl_window_options::PRESENTS::CANVAS_MULTISAMPLING
    );
    if (options.canvas_multisampling == -1)
    {
        options.canvas_multisampling = max_samples;
    }
}

} // namespace

#pragma region helpers

/*
// NOLINTBEGIN(misc-unused-parameters)
void GLAPIENTRY opengl_debug_message_callback(
    GLenum        source,
    GLenum        type,
    GLuint        id,
    GLenum        severity,
    GLsizei       length,
    const GLchar* message,
    const void*   userParam
)
// NOLINTEND(misc-unused-parameters)
{
    auto debug_source   = gl_debug_source_from_original(source);
    auto debug_type     = gl_debug_type_from_original(type);
    auto debug_severity = gl_debug_severity_from_original(severity);
    std::cout << "GL CALLBACK ["
              << "source:" << gl_debug_source_str(debug_source) << "; "
              << "type:" << gl_debug_type_str(debug_type) << "; "
              << "siverity:" << gl_debug_severity_str(debug_severity) << "; "
              << "id:" << id << "]: " << message << "\n";
}
*/

#pragma endregion

#pragma region static_callbacks

void gl_window_context::__context_key_callback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods
)
{
    auto* window_context_ptr
        = reinterpret_cast<gl_window_context*>(glfwGetWindowUserPointer(window));

    window_context_ptr->__key_processing(key, scancode, action, mods);
}

void gl_window_context::__context_cursor_position_callback(
    GLFWwindow* window,
    double      xpos,
    double      ypos
)
{
    auto* window_context_ptr
        = reinterpret_cast<gl_window_context*>(glfwGetWindowUserPointer(window));
    window_context_ptr->__cursor_position_processing(xpos, ypos);
}

void gl_window_context::__context_mouse_button_callback(
    GLFWwindow* window,
    int         button,
    int         action,
    int         mods
)
{
    auto* window_context_ptr
        = reinterpret_cast<gl_window_context*>(glfwGetWindowUserPointer(window));
    window_context_ptr->__mouse_button_processing(button, action, mods);
}

void gl_window_context::__change_position_callback(GLFWwindow* window, int x_pos, int y_pos)
{
    auto* window_context_ptr
        = reinterpret_cast<gl_window_context*>(glfwGetWindowUserPointer(window));
    window_context_ptr->__position_processing(x_pos, y_pos);
}

void gl_window_context::__resize_callback(GLFWwindow* window, int width, int height)
{
    auto* window_context_ptr
        = reinterpret_cast<gl_window_context*>(glfwGetWindowUserPointer(window));
    window_context_ptr->__resize_processing(width, height);
}

void gl_window_context::__context_framebuffer_size_callback(
    GLFWwindow* window,
    int         width,
    int         height
)
{
    auto* window_context_ptr
        = reinterpret_cast<gl_window_context*>(glfwGetWindowUserPointer(window));
    window_context_ptr->__viewport_value = c_m::size2i(width, height);

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}

#pragma endregion

#pragma region processing

void gl_window_context::__processing()
{
    while (__processing_flag && !static_cast<bool>(glfwWindowShouldClose(__window_handler)))
    {
        glfwPollEvents();

        if (__gl_win_options.imgui)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        __window_processor->process(*this);
        __processing_signal_handler(*this);

        if (__gl_win_options.imgui)
        {
            ImGui::Render();
            auto* draw_data = ImGui::GetDrawData();
            if (draw_data != nullptr) ImGui_ImplOpenGL3_RenderDrawData(draw_data);
        }

        glfwSwapBuffers(__window_handler);
    }
}

// NOLINTNEXTLINE(misc-unused-parameters)
void gl_window_context::__key_processing(int key, int scancode, int action, int mods)
{
    key_event event;
    event.key    = static_cast<key_type>(key);
    event.action = input_types_auxiliary::get_input_action_from_glfw(action);

    if (__window_processor != nullptr) __window_processor->on_key_event(event);
    __key_event_signal_handler(event);
}

void gl_window_context::__cursor_position_processing(double xpos, double ypos)
{
    cursor_event event;
    event.x = xpos;
    event.y = ypos;

    if (__window_processor != nullptr) __window_processor->on_cursor_event(event);
    __cursor_event_signal_handler(event);
}

// NOLINTNEXTLINE(misc-unused-parameters)
void gl_window_context::__mouse_button_processing(int button, int action, int mods)
{
    mouse_button_event event;
    event.button = static_cast<mouse_button>(button);
    event.action = input_types_auxiliary::get_input_action_from_glfw(action);

    if (__window_processor != nullptr) __window_processor->on_mouse_button_event(event);
    __mouse_button_event_signal_handler(event);
}

void gl_window_context::__position_processing(int x_pos, int y_pos)
{
    auto pos = c_m::point2i { x_pos, y_pos };
    __win_options.area.set_position(pos);

    if (__window_processor != nullptr) __window_processor->on_change_position(pos);
    __change_position_signal_handler(pos);
}

void gl_window_context::__resize_processing(int width, int height)
{
    auto size = c_m::size2i { width, height };
    __win_options.area.set_size(size);

    if (__window_processor != nullptr) __window_processor->on_resize(size);
    __resize_signal_handler(size);
}

#pragma endregion

#pragma region construct_and_destruct

gl_window_context::gl_window_context(
    gl_main_context&         main_context,
    const window_options&    win_options,
    const gl_window_options& gl_win_options,
    gl_monitor_context*      monitor
) :
    __main_context(main_context)
{
    __monitor = monitor;

    __processing_flag = false;

    auto window_position = win_options.area.position();
    auto window_size     = win_options.area.size();

    __win_options    = win_options;
    __gl_win_options = gl_win_options;

    __window_handler = nullptr;

    auto validate_glfw_window_nullptr = [](GLFWwindow* window_handler)
    {
        if (window_handler == nullptr)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
                << c_f::error_tag_message("cannot create glfw window");
        }
    };

    glfwDefaultWindowHints();

    // TODO deleate after checking

    if (win_options.mode == window_mode::fullscreen)
    {
        if (__monitor == nullptr)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(
                "not passed monitor context for create window in fullscreen mode."
            );
        }
        __window_handler = glfwCreateWindow(
            window_size.width,
            window_size.height,
            "",
            __monitor->get_handler(),
            nullptr
        );
        validate_glfw_window_nullptr(__window_handler);
    }
    else if (win_options.mode == window_mode::borderless)
    {
        if (__monitor == nullptr)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(
                "not passed monitor context for create window in borderless mode."
            );
        }
        auto monitor_size = __monitor->get_size();
        auto monitor_pos  = __monitor->get_work_area().position();
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        __window_handler
            = glfwCreateWindow(monitor_size.width, monitor_size.height, "", nullptr, nullptr);
        glfwSetWindowPos(__window_handler, monitor_pos.x, monitor_pos.y);
    }
    else if (win_options.mode == window_mode::windowed)
    {
        __window_handler
            = glfwCreateWindow(window_size.width, window_size.height, "", nullptr, nullptr);
        validate_glfw_window_nullptr(__window_handler);
        glfwSetWindowPos(__window_handler, window_position.x, window_position.y);
    }

    if (__window_handler == nullptr)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
            << c_f::error_tag_message("error. cannot create GLFWWindow handler.");
    }

    glfwMakeContextCurrent(__window_handler);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
            << c_f::error_tag_message("Failed to initialize glew");
    }
}

gl_window_context::~gl_window_context()
{
    if (__window_handler != nullptr)
    {
        if (__gl_win_options.imgui)
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();

            ImGui::DestroyContext();
        }
        glfwDestroyWindow(__window_handler);
    }
}

#pragma endregion

#pragma region interface_signals

c_f::signal<void(key_event)>& gl_window_context::get_key_event_signal()
{
    return __key_event_signal_handler;
}

c_f::signal<void(mouse_button_event)>& gl_window_context::get_mouse_button_event_signal()
{
    return __mouse_button_event_signal_handler;
}

c_f::signal<void(cursor_event)>& gl_window_context::get_cursor_event_signal()
{
    return __cursor_event_signal_handler;
}

c_f::signal<void(c_m::point2i)>& gl_window_context::get_change_position_signal()
{
    return __change_position_signal_handler;
}

c_f::signal<void(c_m::size2i)>& gl_window_context::get_resize_signal()
{
    return __resize_signal_handler;
}

c_f::signal<void(i_window_context&)>& gl_window_context::get_processing_signal()
{
    return __processing_signal_handler;
}

#pragma endregion

#pragma region interface_impl

c_m::rectangle_i gl_window_context::get_area() const { return __win_options.area; }

c_m::size2i gl_window_context::get_viewport() const { return __viewport_value; }

window_mode gl_window_context::gl_window_context::get_window_mode() const
{
    return __win_options.mode;
}

void gl_window_context::set_processor(std::shared_ptr<a_window_processor> processor)
{
    __window_processor = processor;
}

void gl_window_context::start_processing()
{
    if (__window_processor == nullptr)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
            << c_f::error_tag_message("Window processor is not setted.");
    }

    std::cout << "Vendor name:" << glGetString(GL_VENDOR) << "\n";
    std::cout << "Version:" << glGetString(GL_VERSION) << "\n";

    validate_and_process_gl_options(__gl_win_options);

    // CHECK. для интеропа между GLFW и  IMGUI
    glfwSwapInterval(1);

    if (__gl_win_options.imgui)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        const ImGuiIO& io = ImGui::GetIO();
        (void)io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        const char* glsl_version = "#version 410";

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(__window_handler, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    // setups callbacks
    glfwSetWindowUserPointer(__window_handler, static_cast<void*>(this));

    glfwSetKeyCallback(__window_handler, gl_window_context::__context_key_callback);
    glfwSetCursorPosCallback(
        __window_handler,
        gl_window_context::__context_cursor_position_callback
    );
    glfwSetMouseButtonCallback(
        __window_handler,
        gl_window_context::__context_mouse_button_callback
    );

    glfwSetWindowPosCallback(__window_handler, gl_window_context::__change_position_callback);
    glfwSetWindowSizeCallback(__window_handler, gl_window_context::__resize_callback);
    glfwSetFramebufferSizeCallback(
        __window_handler,
        gl_window_context::__context_framebuffer_size_callback
    );

    int width;
    int height;
    glfwGetFramebufferSize(__window_handler, &width, &height);
    glViewport(0, 0, width, height);
    __viewport_value = c_m::size2i(width, height);

    __window_processor->init(*this);

    __processing_flag = true;

    __processing();
}

void gl_window_context::stop_processing() { __processing_flag = false; }

void gl_window_context::reset_window_options(
    window_options     win_options,
    i_monitor_context* monitor_ptr
)
{
    glfwDefaultWindowHints();

    __win_options = win_options;

    auto window_position = win_options.area.position();
    auto window_size     = win_options.area.size();

    if (win_options.mode == window_mode::fullscreen)
    {
        if (monitor_ptr == nullptr)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(
                "not passed monitor context for create window in fullscreen mode."
            );
        }

        auto*              gl_monitor_ptr  = gl_monitor_context::validate_and_cast_ptr(monitor_ptr);
        auto*              monitor_handler = gl_monitor_ptr->get_handler();
        const GLFWvidmode* mode            = glfwGetVideoMode(monitor_handler);

        glfwSetWindowMonitor(
            __window_handler,
            monitor_handler,
            0,
            0,
            window_size.width,
            window_size.height,
            mode->refreshRate
        );
        __monitor = gl_monitor_ptr;
    }
    else if (win_options.mode == window_mode::borderless)
    {
        if (monitor_ptr == nullptr)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(
                "not passed monitor context for create window in borderless mode."
            );
        }

        auto*              gl_monitor_ptr  = gl_monitor_context::validate_and_cast_ptr(monitor_ptr);
        auto*              monitor_handler = gl_monitor_ptr->get_handler();
        const GLFWvidmode* mode            = glfwGetVideoMode(monitor_handler);

        auto monitor_size = gl_monitor_ptr->get_size();
        auto monitor_pos  = gl_monitor_ptr->get_work_area().position();

#if defined(CALLISTO_OS_WINDOWS)
        glfwSetWindowAttrib(__window_handler, GLFW_DECORATED, GLFW_FALSE);
        HWND hwnd = glfwGetWin32Window(__window_handler);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, mode->width, mode->height, SWP_SHOWWINDOW);
#else
        glfwSetWindowMonitor(
            __window_handler,
            nullptr,
            monitor_pos.x,
            monitor_pos.y,
            monitor_size.width,
            monitor_size.height,
            GLFW_DONT_CARE
        );

        glfwSetWindowAttrib(__window_handler, GLFW_DECORATED, GLFW_FALSE);
#endif
        __monitor = gl_monitor_ptr;
    }
    else if (win_options.mode == window_mode::windowed)
    {
        glfwSetWindowMonitor(
            __window_handler,
            nullptr,
            window_position.x,
            window_position.y,
            window_size.width,
            window_size.height,
            GLFW_DONT_CARE
        );
        glfwSetWindowAttrib(__window_handler, GLFW_DECORATED, GLFW_TRUE);

        __monitor = nullptr;
    }
}

#pragma region getters_and_setters

i_monitor_context* gl_window_context::get_monitor() { return __monitor; }

GLFWwindow* gl_window_context::get_window_handler() { return __window_handler; }

gl_window_options gl_window_context::get_gl_win_options() const { return __gl_win_options; }

#pragma endregion

} // namespace callisto::graphics