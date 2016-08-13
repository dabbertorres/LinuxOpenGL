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
			static constexpr Color Black() { return{}; }
			static constexpr Color Gray() { return{128, 128, 128}; }
			static constexpr Color White() { return{255, 255, 255}; }
			static constexpr Color Red() { return{255, 0, 0}; }
			static constexpr Color Green() { return{0, 255, 0}; }
			static constexpr Color Blue() { return{0, 0, 255}; }
			static constexpr Color Magenta() { return{255, 0, 255}; }
			static constexpr Color Yellow() { return{255, 255, 0}; }
			static constexpr Color Cyan() { return{0, 255, 255}; }
			static constexpr Color Transparent() { return{0, 0, 0, 0}; }

			constexpr static Color fromFloats(float r, float g, float b, float a = 1.f)
			{
				return{static_cast<byte>(r * 255), static_cast<byte>(g * 255), static_cast<byte>(b * 255), static_cast<byte>(a * 255)};
			}

			constexpr Color()
				: Color(0, 0, 0)
			{}

			constexpr Color(byte r, byte g, byte b)
				: Color(r, g, b, 255)
			{}

			constexpr Color(byte r, byte g, byte b, byte a)
				: r(r), g(g), b(b), a(a)
			{}

			constexpr explicit Color(std::uint32_t integer)
				: Color(integer >> 24 & 0xff,
						integer >> 16 & 0xff,
						integer >> 8 & 0xff,
						integer & 0xff)
			{}

			// don't forget about endian-ness!
			std::uint32_t asUintRGBA();
			std::uint32_t asUintBGRA();

			float rf() const;
			float gf() const;
			float bf() const;
			float af() const;

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
