#pragma once

// 3rd party
#include <callisto/math/primitives.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

namespace c_m = callisto::math;

class gl_location
{
    GLint _location;

public:
    // construct and destruct
    inline gl_location() : _location(-1) {};

    inline gl_location(GLint location) { _location = location; }

    // getters and setters
    GLint get_idx() const { return _location; }

    // methods
    inline bool is_exist() { return _location >= 0; }

#pragma region uniform_methods

    // 1f
    inline void uniform_1f(float value) { glUniform1f(_location, value); }

    // 2f

    inline void uniform_2f(float v1, float v2) { glUniform2f(_location, v1, v2); }

    inline void uniform_2f(const glm::vec2& v) { glUniform2f(_location, v.x, v.y); }

    inline void uniform_2f(const c_m::alg_tuple2f& t) { glUniform2f(_location, t.v1, t.v2); }

    // 3f
    inline void uniform_2f(float v1, float v2, float v3) { glUniform3f(_location, v1, v2, v3); }

    inline void uniform_3f(const glm::vec3& v) { glUniform3f(_location, v.x, v.y, v.z); }

    inline void uniform_3f(const c_m::alg_tuple3f& t) { glUniform3f(_location, t.v1, t.v2, t.v3); }

    // 4f
    inline void uniform_4f(float v1, float v2, float v3, float v4)
    {
        glUniform4f(_location, v1, v2, v3, v4);
    }

    inline void uniform_4f(const glm::vec4& v) { glUniform4f(_location, v.x, v.y, v.z, v.w); }

    // 1i
    inline void uniform_1i(int value) { glUniform1i(_location, value); }

    // 2i
    inline void uniform_2i(int32_t v1, int32_t v2) { glUniform2i(_location, v1, v2); }

    inline void uniform_2i(const glm::vec<2, int32_t, glm::defaultp>& vec)
    {
        glUniform2i(_location, vec.x, vec.y);
    }

    inline void uniform_2i(const c_m::alg_tuple2i& t) { glUniform2i(_location, t.v1, t.v2); }

    // 3i
    inline void uniform_3i(int32_t v1, int32_t v2, int32_t v3)
    {
        glUniform3i(_location, v1, v2, v3);
    }

    inline void uniform_3i(const glm::vec<3, int32_t, glm::defaultp>& vec)
    {
        glUniform3i(_location, vec.x, vec.y, vec.z);
    }

    // 4i
    inline void uniform_4i(uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4)
    {
        glUniform4i(_location, v1, v2, v3, v4);
    }

    inline void uniform_4i(const glm::vec<4, int32_t, glm::defaultp>& vec)
    {
        glUniform4i(_location, vec.x, vec.y, vec.z, vec.w);
    }

    // matrix
    template<typename int_type>
    inline void
    uniform_matrix_4fv(int_type location, GLsizei count, bool transpose, float* matrix_ptr)
    {
        glUniformMatrix4fv(_location, count, static_cast<GLboolean>(transpose), matrix_ptr);
    }

    template<typename int_type>
    inline void uniform_matrix_4fv(int_type location, GLsizei count, bool transpose, glm::mat4& mat)
    {
        glUniformMatrix4fv(
            _location,
            count,
            static_cast<GLboolean>(transpose),
            glm::value_ptr(mat)
        );
    }

#pragma endregion
};

} // namespace callisto::graphics