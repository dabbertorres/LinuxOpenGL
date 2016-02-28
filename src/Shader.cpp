#include "Shader.hpp"

#include <vector>
#include <sstream>

#pragma warning(push, 0)
#include "gl_glCore33.hpp"
#pragma warning(pop)

namespace dbr
{
	namespace gl
	{
		Shader::Shader(Type t)
		:	handleVal(0),
			typeVal(t)
		{}

		Shader::~Shader()
		{
			gl::DeleteShader(handleVal);
		}

		void Shader::load(std::istream& in)
		{
			// enable throwing exceptions
			in.exceptions(std::istream::failbit);

			in.seekg(0, std::istream::end);
			std::size_t end = static_cast<std::size_t>(in.tellg());
			in.seekg(0, std::istream::beg);

			// read whole stream
			std::string file(end, 0);
			const char* contents = file.c_str();
			in.read(&file[0], end);

			handleVal = gl::CreateShader(gl::VERTEX_SHADER);
			gl::ShaderSource(handleVal, 1, &contents, nullptr);
			gl::CompileShader(handleVal);

			int status = 0;
			gl::GetShaderiv(handleVal, gl::COMPILE_STATUS, &status);

			if(!status)
			{
				std::string log(512, 0);
				gl::GetShaderInfoLog(handleVal, log.length(), nullptr, &log[0]);

				gl::DeleteShader(handleVal);

				std::ostringstream oss;
				oss << "Shader compilation failed: ";
				oss << log;
				throw std::runtime_error(oss.str());
			}
		}

		glHandle Shader::handle() const
		{
			return handleVal;
		}

		Shader::Type Shader::type() const
		{
			return typeVal;
		}
	}
}
