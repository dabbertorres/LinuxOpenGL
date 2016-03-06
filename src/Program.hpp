#ifndef DBR_GL_PROGRAM_HPP
#define DBR_GL_PROGRAM_HPP

#include "Core.hpp"

#include "Shader.hpp"
#include "Uniform.hpp"

#include <map>

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

				HandleU handle() const;

				Uniform getUniform(const std::string& name);
				HandleI getAttribute(const std::string& name);

			private:
				void link(std::initializer_list<Shader>&& shaders);

				HandleU handleVal;

				// caching requested Uniforms
				std::map<std::string, Uniform> uniforms;

				// caching requested attributes
				std::map<std::string, HandleI> attributes;
		};

		template<typename... Ss>
		void Program::link(const Ss&... ss)
		{
			link({std::forward<const Shader&>(ss)...});
		}
	}
}

#endif
