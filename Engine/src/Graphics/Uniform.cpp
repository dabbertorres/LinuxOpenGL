#include "Uniform.hpp"

#pragma warning(push, 0)
#include "opengl/gl_glCore33.hpp"

#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "Graphics/Program.hpp"

namespace dbr
{
    namespace eng
    {
        namespace gfx
        {
            Uniform::Uniform(const Program& prog, HandleI id)
                : handleVal(id),
                programHandleVal(prog.handle())
            {}

            HandleI Uniform::handle() const
            {
                return handleVal;
            }

            HandleU Uniform::programHandle() const
            {
                return programHandleVal;
            }

            void Uniform::set(float f)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform1f(handleVal, f);
            }

            void Uniform::set(int i)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform1i(handleVal, i);
            }

            void Uniform::set(unsigned int u)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform1ui(handleVal, u);
            }

            void Uniform::set(float f0, float f1)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform2f(handleVal, f0, f1);
            }

            void Uniform::set(int i0, int i1)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform2i(handleVal, i0, i1);
            }

            void Uniform::set(unsigned int u0, unsigned int u1)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform2ui(handleVal, u0, u1);
            }

            void Uniform::set(float f0, float f1, float f2)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform3f(handleVal, f0, f1, f2);
            }

            void Uniform::set(int i0, int i1, int i2)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform3i(handleVal, i0, i1, i2);
            }

            void Uniform::set(unsigned int u0, unsigned int u1, unsigned int u2)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform3ui(handleVal, u0, u1, u2);
            }

            void Uniform::set(float f0, float f1, float f2, float f3)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4f(handleVal, f0, f1, f2, f3);
            }

            void Uniform::set(int i0, int i1, int i2, int i3)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4i(handleVal, i0, i1, i2, i3);
            }

            void Uniform::set(unsigned int u0, unsigned int u1, unsigned int u2, unsigned int u3)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4ui(handleVal, u0, u1, u2, u3);
            }

            void Uniform::set(const glm::vec2& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform2f(handleVal, vec.x, vec.y);
            }

            void Uniform::set(const glm::ivec2& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform2i(handleVal, vec.x, vec.y);
            }

            void Uniform::set(const glm::uvec2& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform2ui(handleVal, vec.x, vec.y);
            }

            void Uniform::set(const glm::vec3& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform3f(handleVal, vec.x, vec.y, vec.z);
            }

            void Uniform::set(const glm::ivec3& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform3i(handleVal, vec.x, vec.y, vec.z);
            }

            void Uniform::set(const glm::uvec3& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform3ui(handleVal, vec.x, vec.y, vec.z);
            }

            void Uniform::set(const glm::vec4& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4f(handleVal, vec.x, vec.y, vec.z, vec.w);
            }

            void Uniform::set(const glm::ivec4 &vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4i(handleVal, vec.x, vec.y, vec.z, vec.w);
            }

            void Uniform::set(const glm::uvec4& vec)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4ui(handleVal, vec.x, vec.y, vec.z, vec.w);
            }

            void Uniform::set(const glm::quat& quat)
            {
                gl::UseProgram(programHandleVal);
                gl::Uniform4f(handleVal, quat.w, quat.x, quat.y, quat.z);
            }

            void Uniform::set(const glm::mat2& mat)
            {
                gl::UseProgram(programHandleVal);
                gl::UniformMatrix2fv(handleVal, 1, false, glm::value_ptr(mat));
            }

            void Uniform::set(const glm::mat3& mat)
            {
                gl::UseProgram(programHandleVal);
                gl::UniformMatrix3fv(handleVal, 1, false, glm::value_ptr(mat));
            }

            void Uniform::set(const glm::mat4& mat)
            {
                gl::UseProgram(programHandleVal);
                gl::UniformMatrix4fv(handleVal, 1, false, glm::value_ptr(mat));
            }
        }
    }
}
