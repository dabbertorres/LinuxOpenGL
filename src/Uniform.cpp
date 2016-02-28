#include "Uniform.hpp"

#pragma warning(push, 0)
#include "gl_glCore33.hpp"
#pragma warning(pop)

#include "Program.hpp"

namespace dbr
{
	namespace gl
	{
		Uniform::Uniform(const Program& prog, glHandle id)
			: handleVal(id),
			programHandleVal(prog.handle())
		{}

		glHandle Uniform::handle() const
		{
			return handleVal;
		}

		glHandle Uniform::programHandle() const
		{
			return programHandleVal;
		}

		void Uniform::set(float f)
		{
			gl::Uniform1f(programHandleVal, f);
		}

		void Uniform::set(int i)
		{
			gl::Uniform1i(programHandleVal, i);
		}

		void Uniform::set(unsigned int u)
		{
			gl::Uniform1ui(programHandleVal, u);
		}

		void Uniform::set(float f0, float f1)
		{
			gl::Uniform2f(programHandleVal, f0, f1);
		}

		void Uniform::set(int i0, int i1)
		{
			gl::Uniform2i(programHandleVal, i0, i1);
		}

		void Uniform::set(unsigned int u0, unsigned int u1)
		{
			gl::Uniform2ui(programHandleVal, u0, u1);
		}

		void Uniform::set(float f0, float f1, float f2)
		{
			gl::Uniform3f(programHandleVal, f0, f1, f2);
		}

		void Uniform::set(int i0, int i1, int i2)
		{
			gl::Uniform3i(programHandleVal, i0, i1, i2);
		}

		void Uniform::set(unsigned int u0, unsigned int u1, unsigned int u2)
		{
			gl::Uniform3ui(programHandleVal, u0, u1, u2);
		}

		void Uniform::set(float f0, float f1, float f2, float f3)
		{
			gl::Uniform4f(programHandleVal, f0, f1, f2, f3);
		}

		void Uniform::set(int i0, int i1, int i2, int i3)
		{
			gl::Uniform4i(programHandleVal, i0, i1, i2, i3);
		}

		void Uniform::set(unsigned int u0, unsigned int u1, unsigned int u2, unsigned int u3)
		{
			gl::Uniform4ui(programHandleVal, u0, u1, u2, u3);
		}

		void Uniform::set(const math::Vector2f& vec)
		{
			gl::Uniform2f(programHandleVal, vec.x, vec.y);
		}

		void Uniform::set(const math::Vector2i& vec)
		{
			gl::Uniform2i(programHandleVal, vec.x, vec.y);
		}

		void Uniform::set(const math::Vector2u& vec)
		{
			gl::Uniform2ui(programHandleVal, vec.x, vec.y);
		}

		void Uniform::set(const math::Vector3f& vec)
		{
			gl::Uniform4f(programHandleVal, vec.x, vec.y, vec.z, vec.w);
		}

		void Uniform::set(const math::Vector3i& vec)
		{
			gl::Uniform4i(programHandleVal, vec.x, vec.y, vec.z, vec.w);
		}

		void Uniform::set(const math::Vector3u& vec)
		{
			gl::Uniform4ui(programHandleVal, vec.x, vec.y, vec.z, vec.w);
		}

		void Uniform::set(const math::Vector4f& vec)
		{
			gl::Uniform4f(programHandleVal, vec.x, vec.y, vec.z, vec.w);
		}

		void Uniform::set(const math::Vector4i& vec)
		{
			gl::Uniform4i(programHandleVal, vec.x, vec.y, vec.z, vec.w);
		}

		void Uniform::set(const math::Vector4u& vec)
		{
			gl::Uniform4ui(programHandleVal, vec.x, vec.y, vec.z, vec.w);
		}

		void Uniform::set(const math::Quaternionf& quat)
		{
			gl::Uniform4f(programHandleVal, quat.w, quat.x, quat.y, quat.z);
		}

		void Uniform::set(const math::Matrix<float, 2, 2>& mat)
		{
			gl::UniformMatrix2fv(programHandleVal, 1, false, mat.data());
		}

		void Uniform::set(const math::Matrix<float, 3, 3>& mat)
		{
			gl::UniformMatrix3fv(programHandleVal, 1, false, mat.data());
		}

		void Uniform::set(const math::Matrix<float, 4, 4>& mat)
		{
			gl::UniformMatrix4fv(programHandleVal, 1, false, mat.data());
		}
	}
}