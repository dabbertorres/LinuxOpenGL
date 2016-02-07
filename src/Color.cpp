#include "Color.hpp"

namespace dbr
{
	namespace gl
	{
		std::uint32_t Color::asInt()
		{
			std::uint32_t ret = 0;

			ret |= static_cast<std::uint32_t>(r) << 24 & 0xff000000;
			ret |= static_cast<std::uint32_t>(g) << 16 & 0xff0000;
			ret |= static_cast<std::uint32_t>(b) << 8 & 0xff00;
			ret |= a;

			return ret;
		}

		constexpr Color Color::Black()
		{
			return{};
		}

		constexpr Color Color::Gray()
		{
			return{128, 128, 128};
		}

		constexpr Color Color::White()
		{
			return{255, 255, 255};
		}

		constexpr Color Color::Red()
		{
			return{255, 0, 0};
		}

		constexpr Color Color::Green()
		{
			return{0, 255, 0};
		}

		constexpr Color Color::Blue()
		{
			return{0, 0, 255};
		}

		constexpr Color Color::Magenta()
		{
			return{255, 0, 255};
		}

		constexpr Color Color::Yellow()
		{
			return{255, 255, 0};
		}

		constexpr Color Color::Cyan()
		{
			return{0, 255, 255};
		}

		constexpr Color Color::Transparent()
		{
			return{0, 0, 0, 0};
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
			left.r = static_cast<byte>(left.r * right);
			left.g = static_cast<byte>(left.g * right);
			left.b = static_cast<byte>(left.b * right);

			return left;
		}

		Color& operator/=(Color& left, float right)
		{
			left.r = static_cast<byte>(left.r / right);
			left.g = static_cast<byte>(left.g / right);
			left.b = static_cast<byte>(left.b / right);

			return left;
		}
	}
}
