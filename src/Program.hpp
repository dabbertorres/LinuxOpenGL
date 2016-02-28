#ifndef DBR_GL_PROGRAM_HPP
#define DBR_GL_PROGRAM_HPP

#include "Core.hpp"

#include "Shader.hpp"
#include "Uniform.hpp"

namespace dbr
{
	namespace gl
	{
		class Program
		{
			public:
				Program();
				~Program();

				// syntax convenience function
				template<typename... Ss>
				void link(const Ss&... ss);

				void use() const;

				glHandle handle() const;

				Uniform getUniform(const std::string& name);

			private:
				void link(std::initializer_list<Shader>&& shaders);

				glHandle handleVal;
		};

		template<typename... Ss>
		void Program::link(const Ss&... ss)
		{
			link({std::forward<const Shader&>(ss)...});
		}
	}
}

#endif
