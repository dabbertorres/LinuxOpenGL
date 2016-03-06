#ifndef DBR_GL_UTIL_IMAGE_STB_IMAGE_HPP
#define DBR_GL_UTIL_IMAGE_STB_IMAGE_HPP

#include <cstdint>
#include <string>
#include <fstream>

#include "stb_image.h"

namespace dbr
{
	namespace gl
	{
		namespace util
		{
			namespace image
			{
				enum class Format : int
				{
					DontCare = 0,
					Gray = 1,
					GrayAlpha = 2,
					RGB = 3,
					RGBA = 4,
				};

				// stbi_load
				inline std::uint8_t* load(const std::string& filename, int &w, int &h, Format &fmt, Format reqFmt = Format::DontCare)
				{
					int ifmt = static_cast<int>(fmt);
					std::uint8_t* ret = stbi_load(filename.c_str(), &w, &h, &ifmt, static_cast<int>(reqFmt));
					fmt = static_cast<Format>(ifmt);

					return ret;
				}

				// stbi_load_from_memory
				inline std::uint8_t* load(const std::uint8_t* buffer, std::size_t len, int &w, int &h, Format &fmt, Format reqFmt = Format::DontCare)
				{
					int ifmt = static_cast<int>(fmt);
					std::uint8_t* ret = stbi_load_from_memory(buffer, len, &w, &h, &ifmt, static_cast<int>(reqFmt));
					fmt = static_cast<Format>(ifmt);

					return ret;
				}
			}
		}
	}
}

#endif
