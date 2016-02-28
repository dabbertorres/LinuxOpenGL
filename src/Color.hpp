#ifndef DBR_GL_COLOR_HPP
#define DBR_GL_COLOR_HPP

#include <cstdint>

namespace dbr
{
	namespace gl
	{
		using byte = std::uint8_t;
		using sbyte = std::int8_t;

		class Color
		{
			public:
				static constexpr Color Black();
				static constexpr Color Gray();
				static constexpr Color White();
				static constexpr Color Red();
				static constexpr Color Green();
				static constexpr Color Blue();
				static constexpr Color Magenta();
				static constexpr Color Yellow();
				static constexpr Color Cyan();
				static constexpr Color Transparent();
				
				constexpr Color()
				:	r(0), g(0), b(0), a(255)
				{}

				constexpr Color(byte r, byte g, byte b)
				:	r(r), g(g), b(b), a(255)
				{}

				constexpr Color(byte r, byte g, byte b, byte a)
				:	r(r), g(g), b(b), a(a)
				{}

				constexpr explicit Color(std::uint32_t integer)
				:	r(integer >> 24 & 0xff),
					g(integer >> 16 & 0xff),
					b(integer >> 8 & 0xff),
					a(integer & 0xff)
				{}

				// don't forget about endian-ness!
				std::uint32_t asUintRGBA();
				std::uint32_t asUintBGRA();

				byte r;
				byte g;
				byte b;
				byte a;
		};

		bool operator==(const Color& left, const Color& right);
		bool operator!=(const Color& left, const Color& right);

		Color operator*(const Color& left, float right);
		Color operator*(float left, const Color& right);

		Color operator/(const Color& left, float right);

		Color& operator*=(Color& left, float right);
		Color& operator/=(Color& left, float right);
	}
}

#endif
