#ifndef DBR_GL_UNIFORM_HPP
#define DBR_GL_UNIFORM_HPP

#include <array>

#include "Core.hpp"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dbr
{
	namespace gl
	{
		class Program;

		class Uniform
		{
			public:
				explicit Uniform(const Program& prog, HandleI id);

				HandleI handle() const;
				HandleU programHandle() const;

				void set(float f);
				void set(int i);
				void set(unsigned int u);

				void set(float f0, float f1);
				void set(int i0, int i1);
				void set(unsigned int u0, unsigned int u1);

				void set(float f0, float f1, float f2);
				void set(int i0, int i1, int i2);
				void set(unsigned int u0, unsigned int u1, unsigned int u2);

				void set(float f0, float f1, float f2, float f3);
				void set(int i0, int i1, int i2, int i3);
				void set(unsigned int u0, unsigned int u1, unsigned int u2, unsigned int u3);

				void set(const glm::vec2& vec);
				void set(const glm::ivec2& vec);
				void set(const glm::uvec2& vec);

				void set(const glm::vec3& vec);
				void set(const glm::ivec3& vec);
				void set(const glm::uvec3& vec);

				void set(const glm::vec4& vec);
				void set(const glm::ivec4& vec);
				void set(const glm::uvec4& vec);

				void set(const glm::quat& quat);
				
				void set(const glm::mat2& mat);
				void set(const glm::mat3& mat);
				void set(const glm::mat4& mat);

			private:
				HandleI handleVal;
				HandleU programHandleVal;
		};
	}
}

#endif
