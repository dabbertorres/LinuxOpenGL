#ifndef DBR_GL_SHADER_HPP
#define DBR_GL_SHADER_HPP

#include <istream>

namespace dbr
{
	namespace gl
	{
		class Shader
		{
			public:
				enum class Type
				{
					Vertex,
					Fragment,
					Geometry,
				};

				Shader(Type t);
				~Shader();

				void load(std::istream& in);

				std::size_t handle() const;
				Type type() const;

			private:
				std::size_t handleVal;
				Type typeVal;
		};
	}
}

#endif
