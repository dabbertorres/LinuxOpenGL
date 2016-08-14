#include "Uniform.hpp"

#pragma warning(push, 0)
#include "opengl/gl_glCore33.hpp"
#pragma warning(pop)

#include "Graphics/Program.hpp"

namespace dbr
{
	namespace gl
	{
		Uniform::Uniform(const Program& prog, HandleI id)
		:	handleVal(id),
			programHandleVal(prog.handle())
		{}

		HandleI Uniform::handle() const
		{
			return handleVal;
		}

		HandleU Uniform::programHandle() const
		{
			return programHandleVal;
		}

		void Uniform::set(float f)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform1f(handleVal, f);
			gl::UseProgram(0);
		}

		void Uniform::set(int i)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform1i(handleVal, i);
			gl::UseProgram(0);
		}

		void Uniform::set(unsigned int u)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform1ui(handleVal, u);
			gl::UseProgram(0);
		}

		void Uniform::set(float f0, float f1)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform2f(handleVal, f0, f1);
			gl::UseProgram(0);
		}

		void Uniform::set(int i0, int i1)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform2i(handleVal, i0, i1);
			gl::UseProgram(0);
		}

		void Uniform::set(unsigned int u0, unsigned int u1)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform2ui(handleVal, u0, u1);
			gl::UseProgram(0);
		}

		void Uniform::set(float f0, float f1, float f2)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform3f(handleVal, f0, f1, f2);
			gl::UseProgram(0);
		}

		void Uniform::set(int i0, int i1, int i2)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform3i(handleVal, i0, i1, i2);
			gl::UseProgram(0);
		}

		void Uniform::set(unsigned int u0, unsigned int u1, unsigned int u2)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform3ui(handleVal, u0, u1, u2);
			gl::UseProgram(0);
		}

		void Uniform::set(float f0, float f1, float f2, float f3)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4f(handleVal, f0, f1, f2, f3);
			gl::UseProgram(0);
		}

		void Uniform::set(int i0, int i1, int i2, int i3)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4i(handleVal, i0, i1, i2, i3);
			gl::UseProgram(0);
		}

		void Uniform::set(unsigned int u0, unsigned int u1, unsigned int u2, unsigned int u3)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4ui(handleVal, u0, u1, u2, u3);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector2f& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform2f(handleVal, vec.x, vec.y);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector2i& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform2i(handleVal, vec.x, vec.y);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector2u& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform2ui(handleVal, vec.x, vec.y);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector3f& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform3f(handleVal, vec.x, vec.y, vec.z);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector3i& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform3i(handleVal, vec.x, vec.y, vec.z);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector3u& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform3ui(handleVal, vec.x, vec.y, vec.z);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector4f& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4f(handleVal, vec.x, vec.y, vec.z, vec.w);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector4i& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4i(handleVal, vec.x, vec.y, vec.z, vec.w);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Vector4u& vec)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4ui(handleVal, vec.x, vec.y, vec.z, vec.w);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Quaternionf& quat)
		{
			gl::UseProgram(programHandleVal);
			gl::Uniform4f(handleVal, quat.w, quat.x, quat.y, quat.z);
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Matrix<float, 2, 2>& mat)
		{
			gl::UseProgram(programHandleVal);
			gl::UniformMatrix2fv(handleVal, 1, false, mat.data());
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Matrix<float, 3, 3>& mat)
		{
			gl::UseProgram(programHandleVal);
			gl::UniformMatrix3fv(handleVal, 1, false, mat.data());
			gl::UseProgram(0);
		}

		void Uniform::set(const math::Matrix<float, 4, 4>& mat)
		{
			gl::UseProgram(programHandleVal);
			gl::UniformMatrix4fv(handleVal, 1, false, mat.data());
			gl::UseProgram(0);
		}
	}
}