#ifndef DBR_GL_PROGRAM_HPP
#define DBR_GL_PROGRAM_HPP

#include "Shader.hpp"

namespace dbr
{
	namespace gl
	{
		class Program
		{
			public:
				using Uniform = int;
				
				Program();
				~Program();

				// syntax convenience function
				template<typename... Ss>
				void link(const Ss&... ss);

				void use() const;

				std::size_t handle() const;

				Uniform getUniform(const std::string& name);

				// gonna need a bunch of overloads
				void setUniform(Uniform uniform, float val);

			private:
				void link(std::initializer_list<Shader> shaders);

				std::size_t handleVal;
		};

		template<typename... Ss>
		void Program::link(const Ss&... ss)
		{
			link({std::forward<Shader>(ss)...});
		}
	}
}

#endif
