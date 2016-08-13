#include "Color.hpp"

namespace dbr
{
	namespace gl
	{
		std::uint32_t Color::asUintRGBA()
		{
			std::uint32_t ret = 0;

			ret |= static_cast<std::uint32_t>(r) << 24 & 0xff000000;
			ret |= static_cast<std::uint32_t>(g) << 16 & 0xff0000;
			ret |= static_cast<std::uint32_t>(b) << 8 & 0xff00;
			ret |= a;

			return ret;
		}

		std::uint32_t Color::asUintBGRA()
		{
			std::uint32_t ret = 0;

			ret |= static_cast<std::uint32_t>(b) << 24 & 0xff000000;
			ret |= static_cast<std::uint32_t>(g) << 16 & 0xff0000;
			ret |= static_cast<std::uint32_t>(r) << 8 & 0xff00;
			ret |= a;

			return ret;
		}

		float Color::rf() const
		{
			return r / 255.f;
		}

		float Color::gf() const
		{
			return g / 255.f;
		}

		float Color::bf() const
		{
			return b / 255.f;
		}

		float Color::af() const
		{
			return a / 255.f;
		}

		bool operator==(const Color& left, const Color& right)
		{
			return left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a;
		}

		bool operator!=(const Color& left, const Color& right)
		{
			return !(left == right);
		}

		Color operator*(const Color& left, float right)
		{
			byte r = static_cast<byte>(left.r * right);
			byte g = static_cast<byte>(left.g * right);
			byte b = static_cast<byte>(left.b * right);

			return{r, g, b, left.a};
		}

		Color operator*(float left, const Color& right)
		{
			return right * left;
		}

		Color operator/(const Color& left, float right)
		{
			byte r = static_cast<byte>(left.r / right);
			byte g = static_cast<byte>(left.g / right);
			byte b = static_cast<byte>(left.b / right);

			return{r, g, b, left.a};
		}

		Color& operator*=(Color& left, float right)
		{
			return left = left * right;
		}

		Color& operator/=(Color& left, float right)
		{
			return left = left / right;
		}
	}
}
