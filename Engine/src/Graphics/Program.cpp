#include "Program.hpp"

#include <sstream>

#pragma warning(push, 0)
#include "opengl/gl_glCore33.hpp"
#pragma warning(pop)

#include "Uniform.hpp"

namespace dbr
{
    namespace eng
    {
        namespace gfx
        {
            void Program::unuse()
            {
                gl::UseProgram(0);
            }

            Program::Program()
                : handleVal(0)
            {}

            Program::~Program()
            {
                gl::DeleteProgram(handleVal);
            }

            void Program::use() const
            {
                gl::UseProgram(handleVal);
            }

            HandleU Program::handle() const
            {
                return handleVal;
            }

            Uniform Program::getUniform(const std::string& name)
            {
                auto find = uniforms.find(name);

                if (find != uniforms.end())
                {
                    return find->second;
                }
                else
                {
                    Uniform uni{*this, gl::GetUniformLocation(handleVal, name.c_str())};
                    uniforms.emplace(name, uni);
                    return uni;
                }
            }

            HandleI Program::getAttribute(const std::string& name)
            {
                auto find = attributes.find(name);

                if (find != attributes.end())
                {
                    return find->second;
                }
                else
                {
                    HandleI h = gl::GetAttribLocation(handleVal, name.c_str());
                    attributes.emplace(name, h);
                    return h;
                }
            }

            void Program::link(std::initializer_list<Shader>&& shaders)
            {
                handleVal = gl::CreateProgram();

                for (auto& s : shaders)
                    gl::AttachShader(handleVal, s.handle());

                gl::LinkProgram(handleVal);

                int status = 0;
                gl::GetProgramiv(handleVal, gl::LINK_STATUS, &status);

                if (!status)
                {
                    std::string log(512, 0);
                    gl::GetProgramInfoLog(handleVal, log.length(), nullptr, &log[0]);

                    gl::DeleteProgram(handleVal);

                    std::ostringstream oss;
                    oss << "Program linking failed: ";
                    oss << log;
                    throw std::runtime_error(oss.str());
                }
            }
        }
    }
}
