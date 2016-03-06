#ifndef DBR_GL_UNIFORM_HPP
#define DBR_GL_UNIFORM_HPP

#include <array>

#include "Core.hpp"

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

#include "Math/Quaternion.hpp"
#include "Math/Matrix.hpp"

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

				void set(const math::Vector2f& vec);
				void set(const math::Vector2i& vec);
				void set(const math::Vector2u& vec);

				void set(const math::Vector3f& vec);
				void set(const math::Vector3i& vec);
				void set(const math::Vector3u& vec);

				void set(const math::Vector4f& vec);
				void set(const math::Vector4i& vec);
				void set(const math::Vector4u& vec);

				void set(const math::Quaternionf& quat);
				
				void set(const math::Matrix<float, 2, 2>& mat);
				void set(const math::Matrix<float, 3, 3>& mat);
				void set(const math::Matrix<float, 4, 4>& mat);

			private:
				HandleI handleVal;
				HandleU programHandleVal;
		};
	}
}

#endif
