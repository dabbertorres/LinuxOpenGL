#include "Program.hpp"

#include <sstream>

#include "gl_glCore33.hpp"

namespace dbr
{
	namespace gl
	{
		Program::Program()
		:	handleVal(0)
		{}

		Program::~Program()
		{
			gl::DeleteProgram(handleVal);
		}

		void Program::use() const
		{
			gl::UseProgram(handleVal);
		}

		std::size_t Program::handle() const
		{
			return handleVal;
		}

		Program::Uniform Program::getUniform(const std::string& name)
		{
			return gl::GetUniformLocation(handleVal, name.c_str());
		}

		void Program::link(std::initializer_list<Shader> shaders)
		{
			handleVal = gl::CreateProgram();

			for(auto& s : shaders)
				gl::AttachShader(handleVal, s.handle());

			gl::LinkProgram(handleVal);

			int status = 0;
			gl::GetProgramiv(handleVal, gl::LINK_STATUS, &status);

			if(!status)
			{
				std::string log(512, 0);
				gl::GetProgramInfoLog(handleVal, log.length(), nullptr, &log[0]);

				gl::DeleteShader(handleVal);

				std::ostringstream oss;
				oss << "Shader compilation failed: ";
				oss << log;
				throw std::runtime_error(oss.str());
			}
		}
	}
}
